#ifndef QTMATERIALCOMBOBOX_H
#define QTMATERIALCOMBOBOX_H


#include <QtWidgets/QComboBox>

class QtMaterialComboBoxPrivate;

class QtMaterialComboBox : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)
public:
    explicit QtMaterialComboBox(QComboBox *parent = nullptr);
    ~QtMaterialComboBox();

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void showPopup() Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialComboBoxPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialComboBox)
    Q_DECLARE_PRIVATE(QtMaterialComboBox)
};

#endif  // QTMATERIALCOMBOBOX_H
