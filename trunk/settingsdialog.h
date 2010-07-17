#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
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

public slots:
    void PassCodeDialogClosed(int result);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
    void on_FrameRateSlider_sliderReleased();

signals:
    void quitApp();
};

#endif // SETTINGSDIALOG_H
