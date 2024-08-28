QT += core gui widgets
QT += statemachine
TEMPLATE = app
CONFIG += c++11
unix {
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
}
win32 {
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/components.lib
}
INCLUDEPATH += $$top_srcdir/include/qmetarial
INCLUDEPATH += $$top_srcdir/include/qmetarial/lib
TARGET = examples-exe
SOURCES += $$files($$top_srcdir/examples/*.cpp)
HEADERS += $$files($$top_srcdir/examples/*.h)
FORMS += $$files($$top_srcdir/examples/*.ui)

RESOURCES += \
    examples.qrc
