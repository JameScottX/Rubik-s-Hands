#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T22:40:42
#
#-------------------------------------------------

QT       += core gui
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = magicCube
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        magic.cpp \
      colorhandle.cpp \
    core.cpp \
    serial.cpp \
    cameraset.cpp

HEADERS += \
        magic.h \
    colorhandle.h \
    core.h \
    serial.h \
    cameraset.h

FORMS += \
        magic.ui \
    cameraset.ui

INCLUDEPATH+=C:/OpenCV_/cv_3.2/opencv/build/include  \
             C:/OpenCV_/cv_3.2/opencv/build/include/opencv  \
             C:/OpenCV_/cv_3.2/opencv/build/include/opencv2

LIBS+= C:/OpenCV_/cv_3.2/opencv/build/x64/vc14/lib/opencv_world320.lib
LIBS+= C:/OpenCV_/cv_3.2/opencv/build/x64/vc14/lib/opencv_world320d.lib

VERSION = 1.0
RC_ICONS = a9.ico

