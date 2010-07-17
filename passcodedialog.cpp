#include "passcodedialog.h"
#include "ui_passcodedialog.h"

PasscodeDialog::PasscodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasscodeDialog)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, 800, 480);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

    ui->lineEdit->clear();
}

PasscodeDialog::~PasscodeDialog()
{
    delete ui;
}

QString PasscodeDialog::getEnteredCode() {
    return ui->lineEdit->text();
}

void PasscodeDialog::clearCode() {
    ui->lineEdit->clear();
    this->setMessageText("Passcode Please:");
}

void PasscodeDialog::setMessageText(QString text) {
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setText("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt; font-weight:600; text-decoration: underline;\">" + text + "</span></p></body></html>");
}

void PasscodeDialog::on_pushButton_clicked()
{
    ui->lineEdit->insert(QString::number(1));
}

void PasscodeDialog::on_pushButton_2_clicked()
{
    ui->lineEdit->insert(QString::number(2));
}

void PasscodeDialog::on_pushButton_3_clicked()
{
    ui->lineEdit->insert(QString::number(3));
}

void PasscodeDialog::on_pushButton_4_clicked()
{
    ui->lineEdit->insert(QString::number(4));
}

void PasscodeDialog::on_pushButton_5_clicked()
{
    ui->lineEdit->insert(QString::number(5));
}

void PasscodeDialog::on_pushButton_6_clicked()
{
    ui->lineEdit->insert(QString::number(6));
}

void PasscodeDialog::on_pushButton_7_clicked()
{
    ui->lineEdit->insert(QString::number(7));
}

void PasscodeDialog::on_pushButton_8_clicked()
{
    ui->lineEdit->insert(QString::number(8));
}

void PasscodeDialog::on_pushButton_9_clicked()
{
    ui->lineEdit->insert(QString::number(9));
}

void PasscodeDialog::on_pushButton_10_clicked()
{
    ui->lineEdit->insert(QString::number(0));
}

void PasscodeDialog::on_buttonBox_accepted()
{

}
