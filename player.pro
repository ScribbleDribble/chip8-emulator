
TEMPLATE = app
TARGET = chip8-player
INCLUDEPATH += . /opt/local/include

QT += widgets gui 

# Input
HEADERS += decode.h display.h registers.h vm.h window.h
SOURCES += main.cpp display.c vm.c decode.c window.cpp
