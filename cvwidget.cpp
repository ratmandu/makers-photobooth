#include "cvwidget.h"
#include "ui_cvwidget.h"

CVWidget::CVWidget(QWidget *parent) :
        QGLWidget(parent),
        ui(new Ui::CVWidget)
{
    ui->setupUi(this);

    // set up storage directory
    if (!QDir(dir.homePath() + "/PBoothPics").exists()) { // PBoothPics folder does not exist in home directory
        // create directory in home folder
        dir.mkdir(dir.homePath() + "/PBoothPics");
    }

    date = QDate::currentDate().toString("MMddyyyy");

    if (!QDir(dir.homePath() + "/PBoothPics/" + date).exists()) { // dated directory does not exist, create it.
        // All of our pictures will be stored in this folder, until the software is started on another date
        dir.mkdir(dir.homePath() + "/PBoothPics/" + date);
    }

    // set path for dir
    dir.setPath(dir.homePath() + "/PBoothPics/" + date);

    // Change the '-1' to specific video device number if needed, or leave it for autodetection
    // (useful to change if machine has multiple cameras attached)
    cam = cvCaptureFromCAM(-1);

    // change this value to basically determine framerate.
    // higher numbers = lower framerate = lower cpu usage
    FrameRateTimer.setInterval(settings.value("FramerateTimer", 33).toInt());

    connect(&FrameRateTimer, SIGNAL(timeout()), this, SLOT(update()));
    FrameRateTimer.start();

    countdownTimer.setInterval(1000);

    imageScanCount = 0;

    connect(&countdownTimer, SIGNAL(timeout()), this, SLOT(CountDownTimerTick()));
    connect(&zbar, SIGNAL(decoded(int,QString)), this, SLOT(Decoded(int,QString)));
    connect(&settingsWindow, SIGNAL(finished(int)), this, SLOT(SettingsDialogClosed(int)));
    connect(&passDialog, SIGNAL(finished(int)), this, SLOT(PasscodeDialogClosed(int)));
    connect(&settingsWindow, SIGNAL(quitApp()), this, SLOT(quitApp()));
}

CVWidget::~CVWidget()
{
    delete ui;
}

void CVWidget::paintEvent(QPaintEvent *) {

    if (!showingSettingsDialog) {

        // create painter which we will draw everything onto
        QPainter painter(this);

        // fill painter with black background
        painter.fillRect(0,0,this->width(), this->height(), Qt::SolidPattern);


        if (!pauseScreen) { // we are not freezing the image, update it from the camera
            // grab new frame from camera
            frame = cvQueryFrame(cam);
            // convert to a format QT can understand
            cvtColor(frame, frame, CV_BGR2RGB);
            // convert to a QImage so we can easily display it and manipulate/save it
            convertedImage = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        }

        // draw image to the widget, aligned to the right of the window
        painter.drawImage(this->width() - convertedImage.width(),0, convertedImage);

        // check for barcode
        if (++imageScanCount >= settings.value("ImageScanInterval", 15).toInt()) {
            imageScanCount = 0;
            zbar.scanImage(QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888).convertToFormat(QImage::Format_RGB32));
        }

        // draw icon bar
        painter.drawImage(QPoint(0,0),QImage(":UI/IconStripe.jpg"));

        // are we in the process of capturing a strip?
        // show the countdown
        // TODO: Make this a little better looking, maybe a graphical bar?
        if (showCountdown) {
            // set pen to white (shows up on black background)
            painter.setPen(QColor::fromRgb(255,255,255));
            // set font to use
            painter.setFont(QFont("Helvetica", 30, QFont::Normal,false));
            // draw number of seconds until picture
            painter.drawText(QPoint(50,210), QString::number(SetupTimeCounter));
        }
    }
}

void CVWidget::Decoded(int type, const QString &data) {
    if (type == ZBAR_QRCODE && (data == "EMERGENCY+BACKDOOR" || data == settings.value("QRValue", "ML256").toString())) {
        pauseScreen = false;
        showingSettingsDialog = false;
        passDialog.showFullScreen();
    }
}

void CVWidget::SettingsDialogClosed(int result) {
    if (result == QDialog::Accepted) {
        FrameRateTimer.setInterval(settings.value("FramerateTimer", 33).toInt());

        pauseScreen = false;
        showingSettingsDialog = false;
    }
}

void CVWidget::PasscodeDialogClosed(int result) {
    if (result == QDialog::Accepted && passDialog.getEnteredCode() == settings.value("Passcode", "4435").toString()) {
        // code is correct
        passDialog.clearCode();
        settingsWindow.showFullScreen();
    } else {
        passDialog.clearCode();
        pauseScreen = false;
        showingSettingsDialog = false;
    }
}

void CVWidget::mouseDoubleClickEvent(QMouseEvent *e) {
    pauseScreen = true;
    showingSettingsDialog = true;
    passDialog.showFullScreen();
}

void CVWidget::mousePressEvent(QMouseEvent *e) {
    if (QRect(0, 0, 160, 150).contains(e->pos())) {
        SetupTimeCounter = settings.value("SetupTimeSeconds", 3).toInt();
        picNumber = settings.value("NumberOfPictures", 4).toInt();
        showCountdown = true;
        countdownTimer.start();
    }
}

void CVWidget::CountDownTimerTick() {
    if (SetupTimeCounter == 0) {
        pauseScreen = true;
        showCountdown = false;
        countdownTimer.setInterval(settings.value("ScreenPauseTime", 3000).toInt());
        SetupTimeCounter = -1;
        return;
    } else if (SetupTimeCounter == -1) {
        saveImage(picNumber);
        pauseScreen = false;
        SetupTimeCounter = settings.value("SetupTimeSeconds", 3).toInt();
        countdownTimer.stop();
        countdownTimer.setInterval(1000);
        if (picNumber > 1) {
            picNumber--;
            countdownTimer.start();
            showCountdown = true;
        } else {
            QString finalFileName(QDateTime::currentDateTime().toString("MMddyyyy-hhmmssap"));
            finalImage.save(dir.absolutePath()+"/"+finalFileName+".jpg");
        }
        return;
    }
    SetupTimeCounter--;
}

void CVWidget::saveImage(int i) {
    if (i == settings.value("NumberOfPictures", 4).toInt()) {
        finalImage = QImage(convertedImage.width(), convertedImage.height()*settings.value("NumberOfPictures", 4).toInt(),QImage::Format_RGB888);
    }
    i--;

    QPainter paint(&finalImage);

    int yPos = 0;
    yPos = (finalImage.height() - (convertedImage.height() * i)) - convertedImage.height();
    paint.drawImage(QPoint(0, yPos), convertedImage);
}

void CVWidget::quitApp() {
    this->parentWidget()->parentWidget()->close();
}
