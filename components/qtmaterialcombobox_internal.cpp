#include "qtmaterialcombobox_internal.h"

QtMaterialComboBoxDelegate::QtMaterialComboBoxDelegate(QObject* parent):QStyledItemDelegate(parent) {};

// set popup item size
QSize QtMaterialComboBoxDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize originSize = QStyledItemDelegate::sizeHint(option, index);
    originSize.setHeight(originSize.height() * 2);
    return originSize;
}

void QtMaterialComboBoxDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const {
    QStyledItemDelegate::initStyleOption(option, index);

            // Check if the index corresponds to the item you want to disable
    // For demonstration, let's disable the item at index 1
    if (index.row() == 1) {
        // option->state &= ~QStyle::State_Enabled; // Disable the item
    }
}

// paint popup item
void QtMaterialComboBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QStyleOptionViewItem customOption = option;
    initStyleOption(&customOption, index);

    QRect newRect = QRect(option.rect.left(), option.rect.top(), option.rect.width(), option.rect.height());

    if(option.state & QStyle::State_MouseOver) {
        // hover
        painter->setPen(QColor(93,160,255));//fillRect(newRect, QColor("#C0C0C0"));
        painter->setBrush(QColor(93,160,255));
        painter->drawRoundedRect(newRect,5,5); // Draw rounded rectangle
    }

    if(option.state & QStyle::State_Selected) {
        // selected
        painter->setPen(QColor(93,160,255));//fillRect(newRect, QColor("#C0C0C0"));
        painter->setBrush(QColor(93,160,255));
        painter->drawRoundedRect(newRect,5,5); // Draw rounded rectangle
    }
    QFont font("黑体", 14); // Font family and size
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(newRect, Qt::AlignLeft | Qt::AlignVCenter ,index.data().toString());

    // QStyledItemDelegate::paint(painter, customOption, index);
}


// ----------------------- QtMaterialComboBoxView --------------------------
QtMaterialComboBoxView::QtMaterialComboBoxView(QWidget *parent) : QListView(parent) {};

void QtMaterialComboBoxView::paintEvent(QPaintEvent *event) {
    QListView::paintEvent(event);
}
