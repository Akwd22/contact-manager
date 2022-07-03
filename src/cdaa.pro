TEMPLATE = subdirs

SUBDIRS += \
    logic \
    storage \
    test_logic \
    ui

CONFIG += \
    ordered \ # Build projects from the first to the last.
    qtc_runnable
