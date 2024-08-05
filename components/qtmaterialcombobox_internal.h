#ifndef QTMATERIALCOMBOBOX_INTERNAL_H
#define QTMATERIALCOMBOBOX_INTERNAL_H

#include <QPainter>
#include <QPainterPath>
#include <QStyledItemDelegate>
#include <QListView>
#include <QStyle>
#include <QProxyStyle>


class QtMaterialComboBoxDelegate : public QStyledItemDelegate {

public:
    QtMaterialComboBoxDelegate(QObject* parent = nullptr);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

class QtMaterialComboBoxView : public QListView {
public:
    QtMaterialComboBoxView(QWidget *parent = nullptr);
    // void paintEvent(QPaintEvent *event) override;
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


};


#endif  // QTMATERIALCOMBOBOX_INTERNAL_H
