#ifndef DIVIDERSETTINGSEDITOR_H
#define DIVIDERSETTINGSEDITOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QCheckBox;
class QSpinBox;
class QComboBox;
class QPushButton;
class QLineEdit;
class QLabel;
QT_END_NAMESPACE

class QtMaterialDivider;

class DividerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DividerSettingsEditor(QWidget *parent = 0);
    ~DividerSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectLineColor();
    void selectTextColor();

private:
    QtMaterialDivider *const m_divider1;
    QtMaterialDivider *const m_divider2;
    QtMaterialDivider *const m_divider3;
    QtMaterialDivider *m_divider4; // Divider with Left Text
    
    QVBoxLayout *m_settingsLayout;
    QCheckBox *m_disabledCheckBox;
    QCheckBox *m_useThemeColorsCheckBox;
    QLineEdit *m_textLineEdit;
    QComboBox *m_textAlignmentComboBox;
    QComboBox *m_lineStyleComboBox;
    QSpinBox *m_thicknessSpinBox;
    QPushButton *m_lineColorButton;
    QPushButton *m_textColorButton;
};

#endif // DIVIDERSETTINGSEDITOR_H