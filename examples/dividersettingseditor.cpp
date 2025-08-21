#include "dividersettingseditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QColorDialog>
#include <QGroupBox>
#include <qtmaterialdivider.h>

DividerSettingsEditor::DividerSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_divider1(new QtMaterialDivider()),
      m_divider2(new QtMaterialDivider("Material Design")),
      m_divider3(new QtMaterialDivider("Right Text"))
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    // Settings panel
    QWidget *settingsWidget = new QWidget;
    layout->addWidget(settingsWidget);

    // Canvas for examples
    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    // Setup settings form
    m_settingsLayout = new QVBoxLayout;
    settingsWidget->setLayout(m_settingsLayout);

    // Disabled checkbox
    m_disabledCheckBox = new QCheckBox("Disabled");
    m_settingsLayout->addWidget(m_disabledCheckBox);

    // Use theme colors checkbox
    m_useThemeColorsCheckBox = new QCheckBox("Use theme colors");
    m_useThemeColorsCheckBox->setChecked(true);
    m_settingsLayout->addWidget(m_useThemeColorsCheckBox);

    // Text input
    QHBoxLayout *textLayout = new QHBoxLayout;
    textLayout->addWidget(new QLabel("Text:"));
    m_textLineEdit = new QLineEdit("Material Design");
    textLayout->addWidget(m_textLineEdit);
    m_settingsLayout->addLayout(textLayout);

    // Text alignment combo
    QHBoxLayout *alignLayout = new QHBoxLayout;
    alignLayout->addWidget(new QLabel("Text Alignment:"));
    m_textAlignmentComboBox = new QComboBox;
    m_textAlignmentComboBox->addItems(QStringList() << "Left" << "Center" << "Right");
    m_textAlignmentComboBox->setCurrentIndex(1); // Center
    alignLayout->addWidget(m_textAlignmentComboBox);
    m_settingsLayout->addLayout(alignLayout);

    // Line style combo
    QHBoxLayout *styleLayout = new QHBoxLayout;
    styleLayout->addWidget(new QLabel("Line Style:"));
    m_lineStyleComboBox = new QComboBox;
    m_lineStyleComboBox->addItems(QStringList() << "Solid" << "Dash" << "Dot");
    styleLayout->addWidget(m_lineStyleComboBox);
    m_settingsLayout->addLayout(styleLayout);

    // Thickness spinner
    QHBoxLayout *thicknessLayout = new QHBoxLayout;
    thicknessLayout->addWidget(new QLabel("Thickness:"));
    m_thicknessSpinBox = new QSpinBox;
    m_thicknessSpinBox->setRange(1, 10);
    m_thicknessSpinBox->setValue(1);
    thicknessLayout->addWidget(m_thicknessSpinBox);
    m_settingsLayout->addLayout(thicknessLayout);

    // Color buttons
    QHBoxLayout *colorLayout = new QHBoxLayout;
    m_lineColorButton = new QPushButton("Line Color");
    m_textColorButton = new QPushButton("Text Color");
    colorLayout->addWidget(m_lineColorButton);
    colorLayout->addWidget(m_textColorButton);
    m_settingsLayout->addLayout(colorLayout);

    // Setup canvas with examples
    QVBoxLayout *canvasLayout = new QVBoxLayout;
    canvas->setLayout(canvasLayout);
    
    canvasLayout->addWidget(new QLabel("Simple Divider:"));
    canvasLayout->addWidget(m_divider1);
    canvasLayout->addSpacing(20);
    
    canvasLayout->addWidget(new QLabel("Divider with Center Text:"));
    canvasLayout->addWidget(m_divider2);
    canvasLayout->addSpacing(20);
    
    canvasLayout->addWidget(new QLabel("Divider with Right Text:"));
    m_divider3->setTextAlignment(QtMaterialDivider::Right);
    canvasLayout->addWidget(m_divider3);
    
    canvasLayout->addStretch();

    setupForm();

    // Connect signals
    connect(m_disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(m_textLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateWidget()));
    connect(m_textAlignmentComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_lineStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(m_thicknessSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(m_lineColorButton, SIGNAL(clicked()), this, SLOT(selectLineColor()));
    connect(m_textColorButton, SIGNAL(clicked()), this, SLOT(selectTextColor()));
}

DividerSettingsEditor::~DividerSettingsEditor()
{
}

void DividerSettingsEditor::setupForm()
{
    updateWidget();
}

void DividerSettingsEditor::updateWidget()
{
    // Update all dividers with current settings
    QtMaterialDivider *dividers[] = {m_divider1, m_divider2, m_divider3};
    
    for (int i = 0; i < 3; ++i) {
        QtMaterialDivider *divider = dividers[i];
        
        divider->setEnabled(!m_disabledCheckBox->isChecked());
        divider->setUseThemeColors(m_useThemeColorsCheckBox->isChecked());
        
        // Set text only for dividers 2 and 3, divider 1 is simple line
        if (i > 0) {
            divider->setText(m_textLineEdit->text());
            
            switch (m_textAlignmentComboBox->currentIndex()) {
                case 0: divider->setTextAlignment(QtMaterialDivider::Left); break;
                case 1: divider->setTextAlignment(QtMaterialDivider::Center); break;
                case 2: divider->setTextAlignment(QtMaterialDivider::Right); break;
            }
        }
        
        switch (m_lineStyleComboBox->currentIndex()) {
            case 0: divider->setLineStyle(QtMaterialDivider::SolidLine); break;
            case 1: divider->setLineStyle(QtMaterialDivider::DashLine); break;
            case 2: divider->setLineStyle(QtMaterialDivider::DotLine); break;
        }
        
        divider->setLineThickness(m_thicknessSpinBox->value());
    }
    
    // Set specific alignment for divider3
    m_divider3->setTextAlignment(QtMaterialDivider::Right);
}

void DividerSettingsEditor::selectLineColor()
{
    QColorDialog dialog;
    dialog.setCurrentColor(m_divider2->lineColor());

    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        for (QtMaterialDivider *divider : {m_divider1, m_divider2, m_divider3}) {
            divider->setLineColor(color);
        }
    }
}

void DividerSettingsEditor::selectTextColor()
{
    QColorDialog dialog;
    dialog.setCurrentColor(m_divider2->textColor());

    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        for (QtMaterialDivider *divider : {m_divider1, m_divider2, m_divider3}) {
            divider->setTextColor(color);
        }
    }
}