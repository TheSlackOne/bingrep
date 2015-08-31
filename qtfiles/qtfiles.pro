TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpthread -lbingrep

SOURCES += \
    ../src/main.cpp \
    ../src/utils.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../src/binfinder.h \
    ../src/bingrep.h \
    ../src/dirtreereader.h \
    ../src/utils.h

OTHER_FILES += \
    ../src/Makefile


unix|win32: LIBS += -L$$PWD/../lib/ -lbingrep

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

TARGET = bingrep
