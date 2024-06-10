#-------------------------------------------------
#
# Project created by QtCreator 2024-05-22T13:33:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bank2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    bankaccount.cpp \
    dialogsec.cpp \
    signinpage.cpp \
    makenewaccount.cpp \
    managecard.cpp \
    cardtocard.cpp \
    make_password.cpp \
    see_inventory.cpp \
    change_password.cpp \
    change_permanent_pass.cpp \
    change_pass_base.cpp


HEADERS  += mainwindow.h \
    bankaccount.h \
    dialogsec.h \
    signinpage.h \
    file_functions.h \
    makenewaccount.h \
    userfile.h \
    managecard.h \
    cardtocard.h \
    bankaccount_copy.h \
    make_password.h \
    see_inventory.h \
    change_password.h \
    change_permanent_pass.h \
    change_pass_base.h

FORMS    += mainwindow.ui \
    dialogsec.ui \
    signinpage.ui \
    makenewaccount.ui \
    managecard.ui \
    cardtocard.ui \
    make_password.ui \
    see_inventory.ui \
    change_password.ui \
    change_permanent_pass.ui \
    change_pass_base.ui

RESOURCES += \
    images.qrc \
    icon.qrc \
    img.qrc
