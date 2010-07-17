#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    this->setGeometry(0, 0, 800, 480);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    connect(&passDialog, SIGNAL(finished(int)), this, SLOT(PassCodeDialogClosed(int)));

    ui->FrameRateSlider->setValue(settings.value("FramerateTimer", 33).toInt());
    ui->FrameTimerLabel->setText(settings.value("FramerateTimer", 33).toString());
    ui->PictureCountSpinbox->setValue(settings.value("NumberOfPictures", 4).toInt());
    ui->SetupTimeSlider->setValue(settings.value("SetupTimeSeconds", 5).toInt());
    ui->SetupTimeLabel->setText(settings.value("SetupTimeSeconds", 5).toString());
    ui->PauseTimeSlider->setValue(settings.value("ScreenPauseTime", 3000).toInt()/1000);
    ui->PauseTimeLabel->setText(QString::number(settings.value("ScreenPauseTime", 3000).toInt()/1000));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

/*void SettingsDialog::setPassDialog(PasscodeDialog *passCodeDialog) {
    passDialog = passCodeDialog;
}*/


void SettingsDialog::PassCodeDialogClosed(int result) {
    if (result == QDialog::Accepted) {
        // what step are we on?
        switch (changeCodeStep) {
        case 0:
            // check if code is correct
            if (passDialog.getEnteredCode() == settings.value("Passcode", "4435").toString()) {
                // code is correct, go to next step
                changeCodeStep++;
                passDialog.clearCode();
                passDialog.setMessageText("Enter New Passcode:");
                passDialog.show();
            } else {
                message.setText("Passcode Incorrect");
            }
            break;

        case 1:
            passcode1 = passDialog.getEnteredCode();
            changeCodeStep++;
            passDialog.clearCode();
            passDialog.setMessageText("Verify New Passcode:");
            passDialog.show();
            break;

        case 2:
            changeCodeStep = 0;
            passcode2 = passDialog.getEnteredCode();
            if ((passcode1 == passcode2) && passcode1.length() >= 4) {
                settings.setValue("Passcode", passcode1);
                passDialog.clearCode();
                message.setText("Passcode Changed Successfully");
                message.show();
            } else {
                // passcodes did not match or are too small
                message.setText("Passcodes did not match or were too short. Try again.");
                message.show();
            }
        }
    }
}

void SettingsDialog::on_FrameRateSlider_sliderReleased()
{
}

void SettingsDialog::on_buttonBox_accepted()
{
    settings.setValue("FramerateTimer", ui->FrameRateSlider->value());
    settings.setValue("NumberOfPictures", ui->PictureCountSpinbox->value());
    settings.setValue("SetupTimeSeconds", ui->SetupTimeSlider->value());
    settings.setValue("ScreenPauseTime", ui->PauseTimeSlider->value()*1000);
}

void SettingsDialog::on_pushButton_clicked()
{
    changeCodeStep = 0;
    passDialog.setMessageText("Enter Current Passcode:");
    passDialog.show();
}

void SettingsDialog::on_pushButton_2_clicked()
{
    emit quitApp();
    this->close();
}

void SettingsDialog::receiveDecodedCode(int type, const QString &data) {
    if (changingQRCode && !confirmQRCode) {
        message.close();
        message.setText("Changing to: \"" + data + "\". Scan again to confirm");
        message.show();
        passcode1 = data;
        confirmQRCode = true;
    } else if (changingQRCode && confirmQRCode) {
        if (passcode1 == data) {
            settings.setValue("QRValue", data);
            message.close();
            message.setText("Successfully changed to: " + data);
            message.show();
        } else {
            message.close();
            message.setText("QR Codes did not match");
            message.show();
        }
        changingQRCode = false;
        confirmQRCode = false;
    }
}

void SettingsDialog::receiveImage(QImage image) {
    displayImage = &image;
    ui->ImageLabel->setPixmap(QPixmap().fromImage(displayImage->scaledToWidth(256, Qt::SmoothTransformation)));
}

void SettingsDialog::on_pushButton_3_clicked()
{
    changingQRCode = true;
    message.setText("Display Code you wish to change to.");
    message.show();
}

void SettingsDialog::on_pushButton_4_clicked()
{
    QDir src;
    QDir end;

    src.setPath(src.homePath()+"/PBoothPics");

    end.setPath(QFileDialog::getExistingDirectory(this, "Select Directory", "/media/"));
    end.mkdir(end.absolutePath()+"/PBoothPics");
    end.cd(end.absolutePath() + "/PBoothPics");
    // make directory tree
    QFileInfoList list = src.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo info = list.at(i);
        end.mkdir(info.baseName());
        // go into folder and copy all files
        src.cd(info.baseName());
        end.cd(info.baseName());
        QFileInfoList files = src.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        for(int j = 1; j < files.size(); ++j) {
            QFileInfo fileinfo = files.at(j);
            QFile::copy(fileinfo.absoluteFilePath(), end.absolutePath()+"/"+fileinfo.fileName());
        }
        src.cdUp();
        end.cdUp();
    }
    message.setText("Finished Dumping images");
    message.show();
}
