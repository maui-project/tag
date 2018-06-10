QT += \
    sql \
    network

HEADERS += \
    $$PWD/tagging.h \
    $$PWD/tagdb.h \

SOURCES += \
    $$PWD/tagging.cpp \
    $$PWD/tagdb.cpp \

DEPENDPATH += \
    $$PWD

INCLUDEPATH += \
     $$PWD

DISTFILES += \
     $$PWD/script.sql


API_VER=1.0
