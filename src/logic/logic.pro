CONFIG -= qt

TEMPLATE = lib

DEFINES += LOGIC_LIBRARY

CONFIG += c++11

SOURCES += \
    contactcollection.cpp \
    contactmodel.cpp \
    date.cpp \
    interactioncollection.cpp \
    interactionmodel.cpp \
    todocollection.cpp \
    todomodel.cpp

HEADERS += \
    collection.h \
    collection_impl.h \
    contactcollection.h \
    contactmodel.h \
    date.h \
    interactioncollection.h \
    interactionmodel.h \
    todocollection.h \
    todomodel.h

# Output dir.
CONFIG(debug, debug|release) { DESTDIR = $$_PRO_FILE_PWD_/../out/debug }
                        else { DESTDIR = $$_PRO_FILE_PWD_/../out/release }

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
