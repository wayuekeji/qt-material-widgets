#include "qtmaterialdivider.h"
#include "qtmaterialdivider_p.h"
#include "lib/qtmaterialstyle.h"
#include <QPainter>
#include <QFontMetrics>

/*!
 * \class QtMaterialDividerPrivate
 * \internal
 */

/*!
 * \internal
 */
QtMaterialDividerPrivate::QtMaterialDividerPrivate(QtMaterialDivider *q)
    : q_ptr(q)
{
}

/*!
 * \internal
 */
QtMaterialDividerPrivate::~QtMaterialDividerPrivate()
{
}

/*!
 * \internal
 */
void QtMaterialDividerPrivate::init()
{
    Q_Q(QtMaterialDivider);

    textAlignment = QtMaterialDivider::Center;
    lineStyle = QtMaterialDivider::SolidLine;
    lineThickness = 1;
    useThemeColors = true;

    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    q->setSizePolicy(policy);
}

/*!
 * \class QtMaterialDivider
 */

QtMaterialDivider::QtMaterialDivider(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new QtMaterialDividerPrivate(this))
{
    d_func()->init();
}

QtMaterialDivider::QtMaterialDivider(const QString &text, QWidget *parent)
    : QWidget(parent)
    , d_ptr(new QtMaterialDividerPrivate(this))
{
    d_func()->init();
    setText(text);
}

QtMaterialDivider::~QtMaterialDivider()
{
}

void QtMaterialDivider::setUseThemeColors(bool value)
{
    Q_D(QtMaterialDivider);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialDivider::useThemeColors() const
{
    Q_D(const QtMaterialDivider);

    return d->useThemeColors;
}

void QtMaterialDivider::setText(const QString &text)
{
    Q_D(QtMaterialDivider);

    if (d->text == text) {
        return;
    }

    d->text = text;
    update();
}

QString QtMaterialDivider::text() const
{
    Q_D(const QtMaterialDivider);

    return d->text;
}

void QtMaterialDivider::setTextAlignment(TextAlignment alignment)
{
    Q_D(QtMaterialDivider);

    if (d->textAlignment == alignment) {
        return;
    }

    d->textAlignment = alignment;
    update();
}

QtMaterialDivider::TextAlignment QtMaterialDivider::textAlignment() const
{
    Q_D(const QtMaterialDivider);

    return d->textAlignment;
}

void QtMaterialDivider::setLineThickness(int thickness)
{
    Q_D(QtMaterialDivider);

    if (d->lineThickness == thickness || thickness <= 0) {
        return;
    }

    d->lineThickness = thickness;
    update();
}

int QtMaterialDivider::lineThickness() const
{
    Q_D(const QtMaterialDivider);

    return d->lineThickness;
}

void QtMaterialDivider::setLineColor(const QColor &color)
{
    Q_D(QtMaterialDivider);

    d->lineColor = color;
    
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialDivider::lineColor() const
{
    Q_D(const QtMaterialDivider);

    if (d->useThemeColors || !d->lineColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->lineColor;
    }
}

void QtMaterialDivider::setTextColor(const QColor &color)
{
    Q_D(QtMaterialDivider);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialDivider::textColor() const
{
    Q_D(const QtMaterialDivider);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialDivider::setLineStyle(LineStyle style)
{
    Q_D(QtMaterialDivider);

    if (d->lineStyle == style) {
        return;
    }

    d->lineStyle = style;
    update();
}

QtMaterialDivider::LineStyle QtMaterialDivider::lineStyle() const
{
    Q_D(const QtMaterialDivider);

    return d->lineStyle;
}

/*!
 * \reimp
 */
QSize QtMaterialDivider::sizeHint() const
{
    Q_D(const QtMaterialDivider);

    if (d->text.isEmpty()) {
        return QSize(-1, qMax(d->lineThickness, 16));
    } else {
        QFontMetrics fm(font());
        return QSize(-1, qMax(fm.height() + 8, d->lineThickness + 8));
    }
}

/*!
 * \reimp
 */
QSize QtMaterialDivider::minimumSizeHint() const
{
    Q_D(const QtMaterialDivider);

    if (d->text.isEmpty()) {
        return QSize(0, qMax(d->lineThickness, 1));
    } else {
        QFontMetrics fm(font());
        return QSize(fm.horizontalAdvance(d->text), qMax(fm.height(), d->lineThickness));
    }
}

/*!
 * \reimp
 */
void QtMaterialDivider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(QtMaterialDivider);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const int centerY = r.height() / 2;

    // Set up pen for the line
    QPen pen(lineColor());
    pen.setWidth(d->lineThickness);
    
    switch (d->lineStyle) {
        case DashLine:
            pen.setStyle(Qt::DashLine);
            break;
        case DotLine:
            pen.setStyle(Qt::DotLine);
            break;
        case SolidLine:
        default:
            pen.setStyle(Qt::SolidLine);
            break;
    }

    painter.setPen(pen);

    if (d->text.isEmpty()) {
        // Draw full width line
        painter.drawLine(r.left(), centerY, r.right(), centerY);
    } else {
        // Draw line with text
        QFontMetrics fm(font());
        const int textWidth = fm.horizontalAdvance(d->text);
        const int textHeight = fm.height();
        const int padding = 16; // Space between text and lines
        
        QRect textRect;
        int lineLeft = r.left();
        int lineRight = r.right();

        switch (d->textAlignment) {
            case Left: {
                textRect = QRect(r.left() + padding, centerY - textHeight/2, textWidth, textHeight);
                lineLeft = textRect.right() + padding;
                break;
            }
            case Right: {
                textRect = QRect(r.right() - textWidth - padding, centerY - textHeight/2, textWidth, textHeight);
                lineRight = textRect.left() - padding;
                break;
            }
            case Center:
            default: {
                textRect = QRect((r.width() - textWidth) / 2, centerY - textHeight/2, textWidth, textHeight);
                lineLeft = r.left();
                lineRight = textRect.left() - padding;
                break;
            }
        }

        // Draw left line (if needed)
        if (lineLeft < lineRight && (d->textAlignment == Center || d->textAlignment == Right)) {
            painter.drawLine(lineLeft, centerY, lineRight, centerY);
        }

        // Draw right line (if needed and for center alignment)
        if (d->textAlignment == Center) {
            int rightLineStart = textRect.right() + padding;
            if (rightLineStart < r.right()) {
                painter.drawLine(rightLineStart, centerY, r.right(), centerY);
            }
        }
        
        // Draw left line for left alignment (right side of text)
        if (d->textAlignment == Left && lineLeft < r.right()) {
            painter.drawLine(lineLeft, centerY, r.right(), centerY);
        }
        
        // Draw right line for right alignment (left side of text) 
        if (d->textAlignment == Right && r.left() < lineRight) {
            painter.drawLine(r.left(), centerY, lineRight, centerY);
        }

        // Draw text
        painter.setPen(textColor());
        painter.drawText(textRect, Qt::AlignCenter, d->text);
    }
}