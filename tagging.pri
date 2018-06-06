QT += sql

HEADERS += \
    $$PWD/tagging.h \
    $$PWD/tagdb.h \

SOURCES += \
    $$PWD/tagging.cpp \
    $$PWD/tagdb.cpp \

DEPENDPATH += \
    $$PWD/tagging

INCLUDEPATH += \
     $$PWD/tagging

DISTFILES += \
     $$PWD/script.sql


API_VER=1.0
