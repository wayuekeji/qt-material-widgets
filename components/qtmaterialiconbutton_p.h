#ifndef QTMATERIALICONBUTTON_P_H
#define QTMATERIALICONBUTTON_P_H

#include <QIcon>
#include <QColor>
#include <QtGlobal>
class QtMaterialIconButton;
class QtMaterialRippleOverlay;
class QColor;
class QIcon;

class QtMaterialIconButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialIconButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialIconButton)

public:
    QtMaterialIconButtonPrivate(QtMaterialIconButton *q);
    virtual ~QtMaterialIconButtonPrivate();

    void init();
    void updateRipple();

    QtMaterialIconButton *const q_ptr;
    QtMaterialRippleOverlay *rippleOverlay;
    QColor color;
    QIcon disabledIcon;
    QColor disabledColor;
    bool useThemeColors;
    bool useColor; // use color or not, if not, use color of image, turn image gray when button diabled
};

#endif  // QTMATERIALICONBUTTON_P_H
