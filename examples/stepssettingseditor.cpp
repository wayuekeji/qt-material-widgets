#include "stepssettingseditor.h"
#include "qtmaterialsteps.h"

stepssettingseditor::stepssettingseditor(QWidget *parent)
    : QWidget{parent}, ui(new Ui::StepsSettingsForm), m_steps(new QtMaterialSteps)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background:white;}");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20,20,20,20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    layout->addWidget(m_steps);
    layout->setAlignment(m_steps, Qt::AlignCenter);


    m_steps->addNewStepBtn("step 1", QRect(0, 0, 200, 30));
    m_steps->addNewStepBtn("step 2", QRect(150, 0, 200, 30));
    m_steps->addNewStepBtn("step 3", QRect(300, 0, 200, 30));
    m_steps->gotoStep(0);

    connect(ui->nextBtn, &QPushButton::clicked ,this,[=](){
        m_steps->nextStep();
    });

}

stepssettingseditor::~stepssettingseditor()
{
    delete ui;
}
