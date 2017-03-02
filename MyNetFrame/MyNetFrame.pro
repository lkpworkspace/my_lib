TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    Common.cpp \
    MySock.cpp \
    MyNet.cpp \
    MyThread.cpp \
    MyEvent.cpp \
    MyApp.cpp

HEADERS += \
    Common.h \
    MySock.h \
    MyNet.h \
    MyThread.h \
    MyEvent.h \
    MyApp.h \
    MyList.h \
    MyVec.h
