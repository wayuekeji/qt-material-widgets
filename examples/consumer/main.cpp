#include <QApplication>
#include <QColor>
#include <QtWidgets/QWidget>
#include <lib/qtmaterialstyle.h>
#include <lib/qtmaterialtheme.h>
#include <qtmaterialprogress.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QtMaterialTheme theme;
    theme.setColor(Material::ThemeColor::Accent1, QColor("#ff4081"));

    QtMaterialProgress progress(&window);
    progress.setProgressType(Material::DeterminateProgress);
    progress.setProgressColor(theme.getColor(Material::ThemeColor::Accent1));
    progress.setBackgroundColor(QtMaterialStyle::instance().themeColor(Material::ThemeColor::Border));
    progress.setValue(50);

    return 0;
}
