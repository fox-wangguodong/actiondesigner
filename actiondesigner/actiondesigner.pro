#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T18:37:29
#
#-------------------------------------------------

QT       += core gui
# 加入OpenGL
QT       += opengl
QT       += serialport


CONFIG += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActionDesigner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglview.cpp \
    objloader.cpp \
    action.cpp \
    pose.cpp \
    poselistview.cpp \
    actionlistview.cpp \
    poselibview.cpp \
    modeinverse.cpp \
    posesettingwidget.cpp \
    exittipdialog.cpp \
    splashwindow.cpp \
    serialportcontroller.cpp

HEADERS  += mainwindow.h \
    openglview.h \
    objloader.h \
    action.h \
    pose.h \
    poselistview.h \
    actionlistview.h \
    poselibview.h \
    modeinverse.h \
    posesettingwidget.h \
    exittipdialog.h \
    splashwindow.h \
    serialportcontroller.h

FORMS    += mainwindow.ui \
    openglview.ui \
    poselistview.ui \
    actionlistview.ui \
    poselibview.ui \
    posesettingwidget.ui \
    exittipdialog.ui \
    splashwindow.ui

macx {
# mac only
}
unix:!macx{
# 链接到OpenGL
LIBS += -lGLU
}
win32 {
# 链接到OpenGL
LIBS += -lopengl32 \
    -lglu32 \
    -lglut \
}


RESOURCES += \
    res.qrc
