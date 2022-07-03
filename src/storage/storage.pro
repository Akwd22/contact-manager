QT += core sql

QT -= gui

TEMPLATE = lib

DEFINES += STORAGE_LIBRARY

CONFIG += c++11

SOURCES += \
    daodatabase.cpp \
    dumpjson.cpp \
    managesqlite.cpp \
    sqlitedaocontact.cpp \
    sqlitedaogeneral.cpp \
    sqlitedaointeraction.cpp \
    sqlitedaotodo.cpp \
    stdqt.cpp

HEADERS += \
    daodatabase.h \
    dumpjson.h \
    idaocontact.h \
    idaogeneral.h \
    idaointeraction.h \
    idaotodo.h \
    idump.h \
    imanagedatabase.h \
    managesqlite.h \
    sqlitedaocontact.h \
    sqlitedaogeneral.h \
    sqlitedaointeraction.h \
    sqlitedaotodo.h \
    stdqt.h \
    storage_global.h

# Output dir.
CONFIG(debug, debug|release) { DESTDIR = $$_PRO_FILE_PWD_/../out/debug }
                        else { DESTDIR = $$_PRO_FILE_PWD_/../out/release }

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# Libraries.
win32:CONFIG(release, debug|release): \
    LIBS += \
        -L$$DESTDIR -llogic

else:win32:CONFIG(debug, debug|release): \
    LIBS += \
        -L$$DESTDIR -llogic

else:unix: \
    LIBS += \
        -L$$DESTDIR -llogic

INCLUDEPATH += \
    $$PWD/../logic

DEPENDPATH += \
    $$PWD/../logic
