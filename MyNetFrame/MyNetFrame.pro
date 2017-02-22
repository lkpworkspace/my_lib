TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    MyProcess.cpp \
    Common.cpp \
    MySock.cpp \
    MyNet.cpp \
    MyThread.cpp \
    MyEvent.cpp \
    MyApp.cpp

HEADERS += \
    MyProcess.h \
    Common.h \
    MySubThread.h \
    MySock.h \
    MyNet.h \
    MyThread.h \
    MyEvent.h \
    MyApp.h
