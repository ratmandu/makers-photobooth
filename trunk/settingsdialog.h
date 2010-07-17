#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QPainter>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include "passcodedialog.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    //void setPassDialog(PasscodeDialog *passCodeDialog);

private:
    Ui::SettingsDialog *ui;
    QSettings settings;
    PasscodeDialog passDialog;
    QString passcode1, passcode2;
    int changeCodeStep;
    QMessageBox message;
    QImage *displayImage;
    bool changingQRCode;
    bool confirmQRCode;
    QDir DumpDir;

public slots:
    void PassCodeDialogClosed(int result);
    void receiveDecodedCode(int type, const QString &data);
    void receiveImage(QImage image);

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
    void on_FrameRateSlider_sliderReleased();

signals:
    void quitApp();
};

#endif // SETTINGSDIALOG_H
