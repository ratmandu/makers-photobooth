#ifndef PASSCODEDIALOG_H
#define PASSCODEDIALOG_H

#include <QDialog>

namespace Ui {
    class PasscodeDialog;
}

class PasscodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasscodeDialog(QWidget *parent = 0);
    ~PasscodeDialog();

    QString getEnteredCode();
    void clearCode();
    void setMessageText(QString text);

private:
    Ui::PasscodeDialog *ui;

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // PASSCODEDIALOG_H
