TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread


HEADERS += \
    ../../src/C/_1va_func.h \
    ../../src/C/_2c++_func_pointer.h \
    ../../src/C/_3c++functional.h \
    ../../src/C/_4c_symbol_level.h \
    ../../src/C/_5_selection_sort.h \
    ../../src/C/my_base64.h \
    ../../src/C/my_list.h \
    ../../src/C++/MyList.h \
    ../../src/C++/MyRingBuf.h \
    ../../src/C++/MyThread.h \
    ../../src/C++/MyTimer.h

SOURCES += main.cpp \
    ../../src/C/my_base64.c \
    ../../src/C++/MyThread.cpp \
    ../../src/C++/MyTimer.cpp
