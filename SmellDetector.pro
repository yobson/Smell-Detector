#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T22:10:55
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmellDetector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    class.cpp \
    loggingwindow.cpp \
    logevent.cpp \
    datapoint.cpp \
    graph.cpp \
    bargraph.cpp \
    statistic.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    class.h \
    loggingwindow.h \
    logevent.h \
    datapoint.h \
    graph.h \
    bargraph.h \
    statistic.h

FORMS    += mainwindow.ui \
    loggingwindow.ui \
    statistic.ui
