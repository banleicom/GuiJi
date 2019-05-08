#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T15:04:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiJi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


qtHaveModule(printsupport): QT += printsupport

#qwt setting

#QWT_ROOT = D:\Qt\Qwt-6.1.3 #qwt控件安装位置，注意与qwtconfig.pri配置文件配合修改
QWT_ROOT = D:\qwt-svn_Qt5.6.2

include ( $${QWT_ROOT}/features/qwt.prf )

#end qwt setting

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scene.cpp \
    mouse.cpp \
    guidocwidget.cpp

HEADERS += \
        mainwindow.h \
    ../build-GuiJi-Desktop_Qt_5_10_1_MinGW_32bit-Debug/ui_mainwindow.h \
    scene.h \
    mouse.h \
    guidocwidget.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    soure.qrc
