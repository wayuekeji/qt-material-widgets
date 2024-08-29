QT += core gui widgets
QT += statemachine
TEMPLATE = app
CONFIG += c++11

LIBS += -L$$top_builddir/components/$(OBJECTS_DIR) -lcomponents
INCLUDEPATH += $$top_srcdir/include/qmetarial
TARGET = examples-exe

SOURCES += $$files($$top_srcdir/examples/*.cpp)
HEADERS += $$files($$top_srcdir/examples/*.h)
FORMS += $$files($$top_srcdir/examples/*.ui)

RESOURCES += \
    examples.qrc
