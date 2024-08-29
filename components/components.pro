QT += core gui widgets
QT += statemachine
TEMPLATE = lib
unix {
CONFIG += so
}
win32 {
CONFIG += dll
}

INCLUDEPATH += $$top_srcdir/include/qmetarial
INCLUDEPATH += $$top_srcdir/include/qmetarial/lib

SUBDIRS += $$top_srcdir/components
SUBDIRS += $$top_srcdir/components/materiallib
SUBDIRS += $$top_srcdir/include/qmetarial
SUBDIRS += $$top_srcdir/include/qmetarial/lib

for(SUBDIR, SUBDIRS) {
    SOURCES += $$files($$SUBDIR/*.cpp)
    HEADERS += $$files($$SUBDIR/*.h)
}

RESOURCES += \
    resources.qrc
