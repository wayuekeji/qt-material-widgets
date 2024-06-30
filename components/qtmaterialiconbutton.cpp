#include "qtmaterialiconbutton.h"
#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialstyle.h"
#include "qtmaterialiconbutton_p.h"
#include <QEvent>
#include <QPainter>
#include <QSize>

/*!
 *  @class QtMaterialIconButtonPrivate
 *  @internal
 */

QtMaterialIconButtonPrivate::QtMaterialIconButtonPrivate(QtMaterialIconButton *q)
    : q_ptr(q)
{
}

QtMaterialIconButtonPrivate::~QtMaterialIconButtonPrivate() {}

void QtMaterialIconButtonPrivate::init()
{
    Q_Q(QtMaterialIconButton);

    rippleOverlay = new QtMaterialRippleOverlay(q->parentWidget());
    useColor = true;
    useThemeColors = true;

    rippleOverlay->installEventFilter(q);

    q->setStyle(&QtMaterialStyle::instance());

    QSizePolicy policy;
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);
}

void QtMaterialIconButtonPrivate::updateRipple()
{
    Q_Q(QtMaterialIconButton);

    QRect r(q->rect());
    r.setSize(QSize(q->width() * 2, q->height() * 2));
    r.moveCenter(q->geometry().center());
    rippleOverlay->setGeometry(r);
}

/*!
 *  @class QtMaterialIconButton
 */

QtMaterialIconButton::QtMaterialIconButton(const QIcon &icon, QWidget *parent)
    : QtMaterialIconButton(icon, icon, parent)
{}

QtMaterialIconButton::QtMaterialIconButton(const QIcon &icon, const QIcon &disabledIcon, QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new QtMaterialIconButtonPrivate(this))
{
    d_func()->init();
    d_ptr->disabledIcon = disabledIcon;
    setIcon(icon);
}

QtMaterialIconButton::~QtMaterialIconButton() {}

/*!
 *  @reimp
 */
QSize QtMaterialIconButton::sizeHint() const
{
    QSize icSize = iconSize();
    return QSize(icSize.width() * 1.2, icSize.height() * 1.2);
}

void QtMaterialIconButton::setDisabledIcon(const QIcon &_disabledIcon)
{
    Q_D(QtMaterialIconButton);
    d->disabledIcon = _disabledIcon;
    update();
}

void QtMaterialIconButton::setUseColor(bool value)
{
    Q_D(QtMaterialIconButton);

    if (d->useColor == value) {
        return;
    }

    d->useColor = value;
    update();
}

bool QtMaterialIconButton::useColor()
{
    Q_D(const QtMaterialIconButton);

    return d->useColor;
}

void QtMaterialIconButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialIconButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialIconButton::useThemeColors() const
{
    Q_D(const QtMaterialIconButton);

    return d->useThemeColors;
}

void QtMaterialIconButton::setColor(const QColor &color)
{
    Q_D(QtMaterialIconButton);

    d->color = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialIconButton::color() const
{
    Q_D(const QtMaterialIconButton);

    if (d->useThemeColors || !d->color.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    }
    return d->color;
}

void QtMaterialIconButton::setDisabledColor(const QColor &color)
{
    Q_D(QtMaterialIconButton);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialIconButton::disabledColor() const
{
    Q_D(const QtMaterialIconButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    }
    return d->disabledColor;
}

QtMaterialIconButton::QtMaterialIconButton(QtMaterialIconButtonPrivate &d, QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  @reimp
 */
bool QtMaterialIconButton::event(QEvent *event)
{
    Q_D(QtMaterialIconButton);

    switch (event->type()) {
        case QEvent::Move:
        case QEvent::Resize:
            d->updateRipple();
            break;
        case QEvent::ParentChange: {
            QWidget *widget;
            if ((widget = parentWidget())) {
                d->rippleOverlay->setParent(widget);
            }
            break;
        }
        default:
            break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  @reimp
 */
bool QtMaterialIconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type()) {
        Q_D(QtMaterialIconButton);

        d->updateRipple();
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  @reimp
 */
void QtMaterialIconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialIconButton);

    d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(), d->rippleOverlay->height()) / 2, iconSize().width());
    emit clicked();

    QAbstractButton::mousePressEvent(event);
}

/*!
 *  @reimp
 */
void QtMaterialIconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(const QtMaterialIconButton);

    QPainter painter(this);
    QPixmap pixmap;
    if(d->useColor) {
        pixmap = icon().pixmap(iconSize());
        QPainter iconPainter(&pixmap);
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pixmap.rect(), isEnabled() ? color() : disabledColor());
    } else {
        if(isEnabled()) {
            pixmap = icon().pixmap(iconSize());
        } else {
            pixmap = d->disabledIcon.pixmap(iconSize());
        }
    }

    QRect r(rect());
    const qreal w = pixmap.width() / 2;
    const qreal h = pixmap.height() / 2;
    painter.drawPixmap(QRect((r.width() - w) / 2, (r.height() - h) / 2, w, h), pixmap.scaled(iconSize() * 5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
