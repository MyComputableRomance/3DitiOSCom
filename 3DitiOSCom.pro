#-------------------------------------------------
#
# Project created by QtCreator 2015-09-14T10:34:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DitiOSCom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogregister.cpp \
    dialogfriends.cpp \
    dialoglogin.cpp \
    dialogaddfriends.cpp \
    dialogupload.cpp \
    filedownloader.cpp \
    dialogdownload.cpp

HEADERS  += mainwindow.h \
    dialogregister.h \
    constant.h \
    dialogfriends.h \
    dialoglogin.h \
    dialogaddfriends.h \
    dialogupload.h \
    filedownloader.h \
    dialogdownload.h

FORMS    += mainwindow.ui \
    dialogregister.ui \
    dialogfriends.ui \
    dialoglogin.ui \
    dialogaddfriends.ui \
    dialogupload.ui \
    dialogdownload.ui
