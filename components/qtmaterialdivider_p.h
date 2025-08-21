#ifndef QTMATERIALDIVIDER_P_H
#define QTMATERIALDIVIDER_P_H

#include <QtGlobal>
#include <QColor>

class QtMaterialDivider;

class QtMaterialDividerPrivate
{
    Q_DISABLE_COPY(QtMaterialDividerPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDivider)

public:
    QtMaterialDividerPrivate(QtMaterialDivider *q);
    ~QtMaterialDividerPrivate();

    void init();

    QtMaterialDivider *const q_ptr;
    QString text;
    QtMaterialDivider::TextAlignment textAlignment;
    QtMaterialDivider::LineStyle lineStyle;
    int lineThickness;
    bool useThemeColors;
    QColor lineColor;
    QColor textColor;
};

#endif // QTMATERIALDIVIDER_P_H