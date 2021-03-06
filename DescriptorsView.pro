#-------------------------------------------------
#
# Project created by QtCreator 2018-06-30T09:21:46
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DescriptorsView
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        Services/fileservice.cpp \
        Services/itemsservice.cpp \
        Services/stringservice.cpp\
        Services/floatservice.cpp \
        DescriptorsWidget/descriptorswidget.cpp \
        DescriptorsWidget/axissettingswidget.cpp \
        DescriptorsModel/dscrtablemodel.cpp \
        DescriptorsModel/descriptor.cpp \
        DescriptorsModel/obj.cpp

HEADERS += \
        mainwindow.h \
        static.h \
        Services/fileservice.h \
        Services/itemsservice.h \
        Services/stringservice.h \ 
        Services/floatservice.h \
        DescriptorsWidget/descriptorswidget.h \
        DescriptorsWidget/axissettingswidget.h \
        DescriptorsModel/dscrtablemodel.h \
        DescriptorsModel/descriptor.h \
        DescriptorsModel/obj.h

FORMS += \
        mainwindow.ui \
        DescriptorsWidget/descriptorswidget.ui \
        DescriptorsWidget/axissettingswidget.ui

RESOURCES += \
    sources.qrc

win32: RC_FILE = iconsource.rc
