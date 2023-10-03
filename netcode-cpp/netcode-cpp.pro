QT = core
QT += network

CONFIG += c++17 cmdline
DESTDIR = ../build

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        connectionhandler.cpp \
        ingress.cpp \
        main.cpp \
        servertcp.cpp \
        serverudp.cpp \
        statistics.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    connectionhandler.h \
    ingress.h \
    servertcp.h \
    serverudp.h \
    statistics.h
