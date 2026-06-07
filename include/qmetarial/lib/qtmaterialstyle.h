#ifndef QTMATERIALSTYLE_H
#define QTMATERIALSTYLE_H

#include "components_global.h"
#include "qtmaterialtheme.h"
#include <QScopedPointer>
#include <QtWidgets/QCommonStyle>

#define MATERIAL_DISABLE_THEME_COLORS                                                                                            \
    if (d->useThemeColors == true) {                                                                                             \
        d->useThemeColors = false;                                                                                               \
    }

class QtMaterialTheme;
class QtMaterialStylePrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialStyle : public QCommonStyle
{
    Q_OBJECT

public:
    inline static QtMaterialStyle &instance();
    ~QtMaterialStyle();

    void setTheme(QtMaterialTheme *theme);
    QColor themeColor(const QString &key) const;
    QColor themeColor(Material::ThemeColor key) const;

protected:
    const QScopedPointer<QtMaterialStylePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QtMaterialStyle)

    QtMaterialStyle();

    QtMaterialStyle(QtMaterialStyle const &);
    void operator=(QtMaterialStyle const &);
};

inline QtMaterialStyle &QtMaterialStyle::instance()
{
    static QtMaterialStyle instance;
    return instance;
}

#endif  // QTMATERIALSTYLE_H
