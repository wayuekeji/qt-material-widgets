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

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    m_combobox->addItem("1");
    m_combobox->addItem("2");
    m_combobox->addItem("3");

    m_combobox->setFontSize(10);
    m_combobox->setBackgroundColor(Qt::red);
    layout->addWidget(m_combobox);
    layout->setAlignment(m_combobox, Qt::AlignCenter);
    connect(ui->addNewBtn, &QPushButton::clicked, this, [=](){
        m_combobox->addItem(ui->newItemContentLineEdit->text().size() > 0 ? ui->newItemContentLineEdit->text() : "empty");
    });
    connect(ui->disabledCheckBox, &QCheckBox::stateChanged, this, [=](int i){
        qInfo() << i << Qt::endl;
        m_combobox->setDisabled(i == Qt::Checked);
    });
    connect(ui->colorToolButton, &QToolButton::clicked, this, [=](bool checked){
        selectColor();
    });
    connect(ui->colorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    setupForm();
}

void ComboBoxSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("colorToolButton" == senderName) {
            m_combobox->setBackgroundColor(color);
            ui->colorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
