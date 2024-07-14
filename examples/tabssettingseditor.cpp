#include "tabssettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialtabs.h>
#include <QDebug>
#include <QPushButton>

TabsSettingsEditor::TabsSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::TabsSettingsForm),
      m_tabs(new QtMaterialTabs)
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
    canvas->setMaximumHeight(300);
    layout->addWidget(m_tabs);
    layout->setAlignment(m_tabs, Qt::AlignHCenter);

    m_tabs->addTab("Media");
    m_tabs->addTab("Playback");
    m_tabs->addTab("Audio");
    m_tabs->addTab("Video");
    m_tabs->addTab("Tools");

    QPushButton *nextBtn = new QPushButton("Next Tab");
    connect(nextBtn, &QPushButton::clicked, this, [=](){
        m_tabs->setCurrentTab(m_tabs->currentIndex() + 1);
    });
    layout->addWidget(nextBtn);

    m_tabs->setMinimumWidth(700);

    setupForm();
    connect(m_tabs, &QtMaterialTabs::currentChanged, this, [](int a) {
        qInfo() << a << Qt::endl;
    });

    // connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));

}

TabsSettingsEditor::~TabsSettingsEditor()
{
    delete ui;
}

void TabsSettingsEditor::setupForm()
{
}

void TabsSettingsEditor::updateWidget()
{
}
