#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T16:28:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_gui
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
        mainwindow.cpp \
    form.cpp \
    help.cpp

HEADERS += \
        mainwindow.h \
    form.h \
    help.h

FORMS += \
        mainwindow.ui \
    form.ui \
    help.ui



INCLUDEPATH += "/usr/local/include/opencv2"

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_flann \
-lopencv_legacy \
-lopencv_ml \
-lopencv_features2d \
-lopencv_calib3d
