# -------------------------------------------------
# Project created by QtCreator 2010-07-28T09:18:44
# -------------------------------------------------
TARGET = TcpServer
TEMPLATE = app
SOURCES += main.cpp \
    tcpserver.cpp \
    server.cpp \
    tcpclientsocket.cpp \
    workthread.cpp \
    workthread2.cpp
HEADERS += tcpserver.h \
    server.h \
    tcpclientsocket.h \
    workthread.h \
    workthread2.h
QT += network
FORMS += dialog.ui
