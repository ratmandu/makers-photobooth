#ifndef CVWIDGET_H
#define CVWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvaux.h>
#include <cxmisc.h>
#include <stdlib.h>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <zbar.h>
#include <QZBar.h>
#include <QZBarImage.h>

#include "settingsdialog.h"
#include "passcodedialog.h"

using namespace zbar;
using namespace cv;

namespace Ui {
    class CVWidget;
}

class CVWidget : public QGLWidget {
    Q_OBJECT
public:
    CVWidget(QWidget *parent = 0);
    ~CVWidget();

public slots:
    void SettingsDialogClosed(int result);
    void PasscodeDialogClosed(int result);
    void quitApp();

protected:
//    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
	QZBar zbar;
    Ui::CVWidget *ui;
	Mat frame, gray;
    QImage convertedImage;
    QImage finalImage;
    QImage finalImageHoriz;
    CvCapture *cam;
    QTimer FrameRateTimer;
    QTimer countdownTimer;
    int PauseTime;
    int imageScanCount;
    int picNumber;
    int SetupTimeCounter;
    bool pauseScreen;
    bool showingSettingsDialog;
    bool showCountdown;
    bool pictureTaken;
    void saveImage(int i);
    QString date;
    QDir dir;
    QSettings settings;
    SettingsDialog settingsWindow;
    PasscodeDialog passDialog;
    bool displayingFinalImage;
	bool replaceFaces;
	vector<Rect> faces;
	int faceDetectCount;
	QImage faceReplace(Mat &src);

private slots:
    void CountDownTimerTick();
    void Decoded(int type, const QString & data);

signals:
    void DecodedForSettingsDialog(int, const QString);
    void sendImageToSettingsDialog(QImage);
};

#endif // CVWIDGET_H
