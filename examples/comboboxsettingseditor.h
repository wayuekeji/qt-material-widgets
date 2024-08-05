#ifndef COMBOBOXSETTINGSEDITOR_H
#define COMBOBOXSETTINGSEDITOR_H

#include <QWidget>
#include "qtmaterialcombobox.h"
#include "ui_comboboxsettingsform.h"

class ComboBoxSettingsEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ComboBoxSettingsEditor(QWidget *parent = nullptr);
    ~ComboBoxSettingsEditor();

signals:

protected:
    Ui::ComboboxSettingsForm *const ui;

protected slots:
    void setupForm();

private:
    void init();
    void selectColor();
    QtMaterialComboBox *const m_combobox;
};

#endif  // COMBOBOXSETTINGSEDITOR_H
