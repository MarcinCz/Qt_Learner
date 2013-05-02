#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T22:37:25
# Project created by QtCreator 2013-04-24T21:13:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pain
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    questionsmodel.cpp \
    question.cpp \
    questionsdialog.cpp

HEADERS  += mainwindow.h \
    questionsmodel.h \
    question.h \
    questionsdialog.h

FORMS    += mainwindow.ui \
    questiondialog.ui

RESOURCES += \
    Images.qrc

