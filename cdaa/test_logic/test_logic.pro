TEMPLATE = app

CONFIG += console c++11

CONFIG -= app_bundle

CONFIG -= qt

SOURCES += \
    main.cpp \
    unit_tests.cpp

HEADERS += \
    unit_tests.h

# Output dir.
CONFIG(debug, debug|release) { DESTDIR = $$_PRO_FILE_PWD_/../out/debug }
                        else { DESTDIR = $$_PRO_FILE_PWD_/../out/release }

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
