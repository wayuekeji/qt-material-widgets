#include "comboboxsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>

ComboBoxSettingsEditor::ComboBoxSettingsEditor(QWidget *parent)
    : QWidget{parent}, ui(new Ui::ComboboxSettingsForm),m_combobox(new QtMaterialComboBox)
{
    init();
}

ComboBoxSettingsEditor::~ComboBoxSettingsEditor(){}

void ComboBoxSettingsEditor::setupForm(){}


void ComboBoxSettingsEditor::init()
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);
    ui->fontSizeDoubleSpinBox->setValue(15);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    m_combobox->setFontSize(15);
    layout->addWidget(m_combobox);
    layout->setAlignment(m_combobox, Qt::AlignCenter);

    connect(ui->addNewBtn, &QPushButton::clicked, this, [=](){
        m_combobox->addItem(ui->newItemContentLineEdit->text().size() > 0 ? ui->newItemContentLineEdit->text() : "empty");
    });
    connect(ui->disabledCheckBox, &QCheckBox::stateChanged, this, [=](int i){
        m_combobox->setDisabled(i == Qt::Checked);
    });
    connect(ui->foregroundColorToolButton, &QToolButton::clicked, this, [=](bool checked){
        selectColor();
    });
    connect(ui->backgroundColorToolButton, &QToolButton::clicked, this, [=](bool checked){
        selectColor();
    });
    connect(ui->fontSizeDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [=](double value){
        m_combobox->setFontSize(value);
    });

    setupForm();
}

void ComboBoxSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("foregroundColorToolButton" == senderName) {
            m_combobox->setForegroundColor(color);
            ui->foregroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
        if ("backgroundColorToolButton" == senderName) {
            m_combobox->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
