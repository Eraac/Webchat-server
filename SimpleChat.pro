#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T10:13:27
#
#-------------------------------------------------

QT      += core websockets sql
QT      -= gui

TARGET  = Server-WebSocket

CONFIG  += console c++11 c++14
CONFIG  -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Entity/client.cpp \
    Model/model.cpp \
    Model/modeluser.cpp \
    Utility/settings.cpp \
    server.cpp \
    Utility/encodepassword.cpp \
    Utility/Handler/handlecommand.cpp \
    Utility/Handler/handleconnection.cpp \
    Utility/Handler/handlemessage.cpp \
    room.cpp

HEADERS += \
    Entity/client.hpp \
    Model/model.hpp \
    Model/modeluser.hpp \
    Utility/settings.hpp \
    server.hpp \
    Utility/encodepassword.hpp \
    Utility/Handler/handlecommand.hpp \
    Utility/Handler/handleconnection.hpp \
    Utility/Handler/handlemessage.hpp \
    Utility/code.hpp \
    room.hpp

DISTFILES +=
