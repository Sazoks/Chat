#-------------------------------------------------
#
# Project created by QtCreator 2020-09-13T19:23:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
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

CONFIG += c++11

SOURCES += \
        authform.cpp \
        channel.cpp \
        conform.cpp \
        functionalforms.cpp \
        listchannels.cpp \
        main.cpp \
        client.cpp \
        mainform.cpp \
        messagewindow.cpp \
        mychan.cpp \
        profileform.cpp \
        regform.cpp \
        user.cpp

HEADERS += \
        authform.h \
        channel.h \
        client.h \
        conform.h \
        functionalforms.h \
        listchannels.h \
        mainform.h \
        messagewindow.h \
        mychan.h \
        profileform.h \
        regform.h \
        user.h

FORMS += \
        authform.ui \
        client.ui \
        conform.ui \
        listchannels.ui \
        mainform.ui \
        messagewindow.ui \
        mychan.ui \
        profileform.ui \
        regform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Client.pro.user
