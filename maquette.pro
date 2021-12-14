QT       += core gui sql printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
CONFIG += c++11
QT += sql
QT += core
QT += printsupport
QT += gui
QT += serialport
CONFIG += c++11
QT += core gui network
QT += charts
QT+= svg


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app
TARGET = wearable
QT += quick quickcontrols2
QT       += core gui quick location

SOURCES += \
    abonnement.cpp \
    arduino.cpp \
    billet.cpp \
    bus.cpp \
    connection.cpp \
    emp.cpp \
    exel.cpp \
    ligne.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    station.cpp \
    statistiques.cpp

HEADERS += \
    abonnement.h \
    arduino.h \
    billet.h \
    bus.h \
    connection.h \
    emp.h \
    exel.h \
    ligne.h \
    mainwindow.h \
    qcustomplot.h \
    station.h \
    statistiques.h

FORMS += \
    mainwindow.ui \
    statistiques.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    qml.qrc
QT += network



QT += location



RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/location/minimal_map
INSTALLS += target
QT += qml network quick positioning location
target.path = $$[QT_INSTALL_EXAMPLES]/location/mapviewer

QT += qml network quick positioning location
CONFIG += qtquickcompiler
