QT += core gui
QT += widgets
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 qt thread debug


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../src/voiture.cpp \
    ../src/parking.cpp \
    ../src/Sockets.cpp \
    ../src/ServerParking.cpp \
    ../src/ToolBox.cpp \
    ../src/SocketVoiture.cpp

HEADERS += \
    mainwindow.hpp \
    ../headers/voiture.hpp \
    ../headers/parking.hpp \
    ../headers/Sockets.hpp \
    ../headers/ServerParking.hpp \
    ../headers/ToolBox.hpp \
    ../headers/SocketVoiture.hpp
FORMS += \
    mainwindow.ui
