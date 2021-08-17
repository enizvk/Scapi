#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T13:28:27
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network

CONFIG += console
TARGET = scapi

TEMPLATE = app
INSTALLS += target
target.path = /home/pi


SOURCES += src/main.cpp\
    src/scapi/siserver.cpp \
    src/scapi/sidispacher.cpp \
    src/scapi/silogger.cpp \
    src/scapi/sitcppipe.cpp \
    src/scapi/silinuxdrv.cpp \
    src/scapi/siglobals.cpp

HEADERS  += \
    wiringPi/include/wiringPi.h \
    src/scapi/idevicedriver.h \
    src/scapi/siserver.h \
    src/scapi/sidispacher.h \
    src/scapi/silogger.h \
    src/scapi/sitcppipe.h \
    src/scapi/silinuxdrv.h \
    src/scapi/siglobals.h

FORMS    +=

#wiring pi library
INCLUDEPATH += wiringPi/include
LIBS += -L"wiringPi/lib" -lwiringPi


RESOURCES += \
    scapi.qrc

#DEFINES += STATIC
#CONFIG += release
CONFIG += static
CONFIG += c++11

QMAKE_LFLAGS   =   -static-libgcc -static-libstdc++
QMAKE_CFLAGS   =   -pthread -ggdb
QMAKE_CXXFLAGS =   -pthread -ggdb

DISTFILES += \
    build/scapi \
    scapi \
    wiringPi/lib/libwiringPi.so



