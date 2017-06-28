# 目标程序的名字
TARGET = main.bin
# 中间文件的存放目录
OBJECTS_DIR = ./TEMP
# 目标程序生成目录
DESTDIR = ./TEMP

# 源文件
SOURCES = main.cpp

# 头文件包含路径
#INCLUDEPATH += .

# 头文件
HEADERS += _1va_func.h \
	_2c++_func_pointer.h \
	_3c++functional.h \
	_4c_symbol_level.h \
    _5_selection_sort.h

# 链接库文件
#LIBS += -L<PATH> -l<链接库>

# 宏定义
#DEFINES

# Qt配置选项
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# 模板
TEMPLATE = app
