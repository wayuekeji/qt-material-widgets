#ifndef QTMATERIALDIVIDER_H
#define QTMATERIALDIVIDER_H

#include <QtWidgets/QWidget>
#include <QColor>
#include "components_global.h"

class QtMaterialDividerPrivate;

class COMPONENTS_EXPORT QtMaterialDivider : public QWidget
{
    Q_OBJECT

public:
    enum TextAlignment {
        Left,
        Center, 
        Right
    };

    enum LineStyle {
        SolidLine,
        DashLine,
        DotLine
    };

    explicit QtMaterialDivider(QWidget *parent = 0);
    explicit QtMaterialDivider(const QString &text, QWidget *parent = 0);
    ~QtMaterialDivider();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setText(const QString &text);
    QString text() const;

    void setTextAlignment(TextAlignment alignment);
    TextAlignment textAlignment() const;

    void setLineThickness(int thickness);
    int lineThickness() const;

    void setLineColor(const QColor &color);
    QColor lineColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setLineStyle(LineStyle style);
    LineStyle lineStyle() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDividerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDivider)
    Q_DECLARE_PRIVATE(QtMaterialDivider)
};

#endif // QTMATERIALDIVIDER_H