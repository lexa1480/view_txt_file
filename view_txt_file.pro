QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += boost164

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
    LIBS += -lboost_system
    LIBS += -lboost_filesystem
    LIBS += -lboost_program_options
    LIBS += -lpthread
    LIBS += -lboost_locale
}
