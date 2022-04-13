#-------------------------------------------------
#
# Project created by QtCreator 2022-04-10T17:06:24
#
#-------------------------------------------------

QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-uctas
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
TARGET = e-uctas
CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.cpp.autosave \
    hakkinda.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

SUBDIRS += \
    uctas.pro



desktop_file.files = e-uctas.desktop
desktop_file.path = /usr/share/applications/
icon.files = icons/e-uctas.svg
icon.path = /usr/share/e-uctas/

win.files = win.mp3
win.path = /usr/share/e-uctas/

click.files = click.mp3
click.path = /usr/share/e-uctas/


INSTALLS += target desktop_file icon win click
target.path = /usr/bin
DISTFILES += \
    e-uctas.desktop
