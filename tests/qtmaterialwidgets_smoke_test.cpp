#include <QColor>
#include <QFile>
#include <QIcon>
#include <QApplication>
#include <QMetaProperty>
#include <QTest>

#include <lib/qtmaterialtheme.h>
#include <qtmaterialprogress.h>

class QtMaterialWidgetsSmokeTest : public QObject
{
    Q_OBJECT

private slots:
    void typedThemeColorCanBeSetAndRead();
    void coreResourcesAreAvailable();
    void progressBackgroundColorIsWritableThroughMetaObject();
};

void QtMaterialWidgetsSmokeTest::typedThemeColorCanBeSetAndRead()
{
    QtMaterialTheme theme;
    const QColor accent("#ff4081");

    QCOMPARE(QString::fromLatin1(Material::themeColorKey(Material::ThemeColor::Accent1)), QString("accent1"));

    theme.setColor(Material::ThemeColor::Accent1, accent);

    QCOMPARE(theme.getColor(Material::ThemeColor::Accent1), accent);
}

void QtMaterialWidgetsSmokeTest::coreResourcesAreAvailable()
{
    QVERIFY(QFile::exists(":/fonts/roboto_regular"));
    QVERIFY(!QIcon(":/icons/icons/toggle/svg/production/ic_check_box_24px.svg").isNull());
    QVERIFY(!QtMaterialTheme::icon("communication", "message").isNull());
}

void QtMaterialWidgetsSmokeTest::progressBackgroundColorIsWritableThroughMetaObject()
{
    QtMaterialProgress progress;
    const QColor background("#123456");
    const QMetaObject *metaObject = progress.metaObject();
    const int propertyIndex = metaObject->indexOfProperty("backgroundColor");

    QVERIFY(propertyIndex >= 0);

    QMetaProperty property = metaObject->property(propertyIndex);
    QVERIFY(property.isWritable());
    QVERIFY(property.write(&progress, background));

    QCOMPARE(progress.backgroundColor(), background);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtMaterialWidgetsSmokeTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "qtmaterialwidgets_smoke_test.moc"
