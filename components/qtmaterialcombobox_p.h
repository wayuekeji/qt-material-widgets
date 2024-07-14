#ifndef QTMATERIALCOMBOBOX_P_H
#define QTMATERIALCOMBOBOX_P_H

#include "lib/qtmaterialtheme.h"
#include <QColor>
#include <QtGlobal>

class QtMaterialComboBox;

class QtMaterialComboBoxPrivate
{
    Q_DISABLE_COPY(QtMaterialComboBoxPrivate)
    Q_DECLARE_PUBLIC(QtMaterialComboBox)
public:
    QtMaterialComboBoxPrivate(QtMaterialComboBox *q);
    virtual ~QtMaterialComboBoxPrivate();

    void init();

    QtMaterialComboBox *const q_ptr;
    QColor backgroundColor;
    QColor foregroundColor;
    qreal cornerRadius;
    qreal fontSize;
    bool useThemeColors;
};

#endif  // QTMATERIALCOMBOBOX_P_H
