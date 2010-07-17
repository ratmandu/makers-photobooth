# -------------------------------------------------
# Project created by QtCreator 2010-06-24T18:13:30
# -------------------------------------------------
QT += network \
    opengl \
    webkit
TARGET = PhotoboothSoft
TEMPLATE = app
SOURCES += main.cpp \
    photobooth.cpp \
    cvwidget.cpp \
    settingsdialog.cpp \
    passcodedialog.cpp
HEADERS += photobooth.h \
    cvwidget.h \
    settingsdialog.h \
    passcodedialog.h
FORMS += photobooth.ui \
    cvwidget.ui \
    settingsdialog.ui \
    passcodedialog.ui
LIBS += -lcv \
    -lhighgui \
    -lcxcore -lzbarqt
INCLUDEPATH = /usr/include/opencv /usr/include/zbar

RESOURCES += \
    images.qrc
