#include "qtmaterialcombobox.h"
#include "qtmaterialcombobox_p.h"
#include "qtmaterialcombobox_internal.h"
#include "lib/qtmaterialstyle.h"
#include <QPainter>

QtMaterialComboBoxPrivate::QtMaterialComboBoxPrivate(QtMaterialComboBox *q) : q_ptr(q) {}

QtMaterialComboBoxPrivate::~QtMaterialComboBoxPrivate(){}

void QtMaterialComboBoxPrivate::init()
{
    Q_Q(QtMaterialComboBox);
    useThemeColors = true;
    fontSize = 10;
    cornerRadius = 3;
    q->setStyle(&QtMaterialStyle::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    QFont font("Roboto", fontSize, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);
}


QtMaterialComboBox::QtMaterialComboBox(QComboBox *parent): QComboBox(parent), d_ptr(new QtMaterialComboBoxPrivate(this))
{
    d_func()->init();
}

void QtMaterialComboBox::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialComboBox);

    d->foregroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialComboBox::foregroundColor() const
{
    Q_D(const QtMaterialComboBox);
    return d->foregroundColor;
}

void QtMaterialComboBox::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialComboBox);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialComboBox::backgroundColor() const
{
    Q_D(const QtMaterialComboBox);

    return d->backgroundColor;
}

void QtMaterialComboBox::setFontSize(qreal size)
{
    Q_D(QtMaterialComboBox);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal QtMaterialComboBox::fontSize() const
{
    Q_D(const QtMaterialComboBox);

    return d->fontSize;
}

// paint combobox
void QtMaterialComboBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(1);
    painter.setClipping(true);

    QRect buttonRect = rect();
    buttonRect.adjust(2, 2, -2, -2); // Adjust the button rectangle for border

    painter.setPen(QPen(Qt::darkGray, 0.5));
    painter.setBrush(Qt::white);

    painter.drawRoundedRect(buttonRect, buttonRect.height() / 5, buttonRect.height() / 5); // Draw rounded rectangle

    QRect textRect = QRect(buttonRect.left() + 10, buttonRect.top(), buttonRect.width(), buttonRect.height());
    QFont font("黑体", 14); // Font family and size
    font.setBold(true); // Set font weight to bold
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, currentText());

    QIcon icon(":/assets/image/down.svg");
    // QIcon icon("qrc:/icons/icons/navigation/svg/production/ic_arrow_downward_24px.svg");
    QPixmap pixmap = icon.pixmap(16, 16); // Adjust the size as needed
    painter.drawPixmap(width() - 32, (height() - 16) / 2, pixmap);

    setItemDelegate(new QtMaterialComboBoxDelegate(this));
}

// show popup
void QtMaterialComboBox::showPopup() {
    QProxyStyle *proxyStyle = new QProxyStyle(style());
    proxyStyle->unpolish(this->view());
    this->view()->setStyle(proxyStyle);

    QComboBox::showPopup();

}
