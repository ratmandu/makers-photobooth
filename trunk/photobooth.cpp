#include "photobooth.h"
#include "ui_photobooth.h"

PhotoBooth::PhotoBooth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhotoBooth)
{
    this->setGeometry(0,0,800,640);
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    //this->showFullScreen();
}

PhotoBooth::~PhotoBooth()
{
    delete ui;
}

void PhotoBooth::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
