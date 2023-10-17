QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YourProjectName
TEMPLATE = app

# Input
SOURCES += main.cpp \
           mainwindow.cpp \
           customwidget.cpp

HEADERS += mainwindow.h \
           customwidget.h

FORMS +=

# Other configurations
CONFIG += c++11
