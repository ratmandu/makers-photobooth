#include <QtGui/QApplication>
#include "photobooth.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Makers Local 256");
    QCoreApplication::setApplicationName("Photobooth Software");
    QCoreApplication::setApplicationVersion("0.1");
    PhotoBooth w;
    w.show();
    return a.exec();
}
