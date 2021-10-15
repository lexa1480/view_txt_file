QT       += core gui

CONFIG += c++98
CONFIG += boost164

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CommandLineArgs.h \
    Cons.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


EXT = ""
linux-g++*:{EXT = ".bin"}
TARGET      = $${TARGET}$${EXT}

unix{
    LIBS += -l:libboost_program_options.a
}
