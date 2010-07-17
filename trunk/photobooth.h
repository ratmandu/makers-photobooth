#ifndef PHOTOBOOTH_H
#define PHOTOBOOTH_H

#include <QMainWindow>

namespace Ui {
    class PhotoBooth;
}

class PhotoBooth : public QMainWindow {
    Q_OBJECT
public:
    PhotoBooth(QWidget *parent = 0);
    ~PhotoBooth();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PhotoBooth *ui;
};

#endif // PHOTOBOOTH_H
