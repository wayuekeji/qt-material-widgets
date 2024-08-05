#include "qtmaterialsteps.h"
#include "qtmaterialsteps_p.h"

#include <QHBoxLayout>

static int currentWidth = 0;

QtMaterialStepsPrivate::QtMaterialStepsPrivate(QtMaterialSteps *q)
    : q_ptr(q), clickable(true), currentStepIndex(0)
{
}

QtMaterialStepsPrivate::~QtMaterialStepsPrivate()
{

}

void QtMaterialStepsPrivate::init()
{

}

void QtMaterialStepsPrivate::gotoStep(int idx)
{
    Q_Q(QtMaterialSteps);
    int stepBtnNum = stepBtns.size();
    for(int i = 0;i < stepBtnNum;++i) {
        if(i == idx) {
            stepBtns[i]->setChecked(true);
            currentStepIndex = i;
            continue;
        }
        stepBtns[i]->setChecked(false);
    }
    emit q->stepChanged(idx);

}

void QtMaterialStepsPrivate::stepBtnClicked(int index)
{
    if(!clickable) {
        return;
    }
    gotoStep(index);
}


QtMaterialSteps::QtMaterialSteps(QWidget *parent)
    : QWidget{parent}
    , d_ptr(new QtMaterialStepsPrivate(this))
{
    Q_D(QtMaterialSteps);
    d_func()->init();

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(0,0,0,0);

    d->container = new QWidget(nullptr);
    d->container->setStyleSheet("QPushButton {border:none;border-radius: 15px; background-color:qlineargradient(x1:0, y1:0.5, x2:1, y2:0.5, stop:0 #aaafbc, stop: 1 #767d8e);} QPushButton:hover, QPushButton:checked {background-color: qlineargradient(x1:0, y1:0.5, x2:1, y2:0.5, stop:0 #0066db, stop: 1 #00e0ba);}");
    hLayout->addWidget(d->container);
    this->setMaximumHeight(100);
    this->setMinimumHeight(100);
}

QtMaterialSteps::~QtMaterialSteps() {

}

void QtMaterialSteps::addNewStepBtn(QString title, QRect geo)
{
    Q_D(QtMaterialSteps);
    QPushButton *newStepBtn = new QPushButton(title, d->container);
    newStepBtn->setCheckable(d->clickable);
    newStepBtn->setGeometry(geo);
    int index = d->stepBtns.size();
    connect(newStepBtn, &QPushButton::clicked, this, [=]() {
        if(!d->clickable) {
            return;
        }
        d->stepBtnClicked(index);
    });
    d->stepBtns.push_back(newStepBtn);
    currentWidth = geo.right();
    this->setFixedWidth(currentWidth + 2); // +2是为了弥补圆角带来的误差
    this->setFixedHeight(geo.bottom());
}

int QtMaterialSteps::nextStep() // 返回跳转后的index
{
    Q_D(QtMaterialSteps);
    if(d->currentStepIndex >= stepNum() - 1) {
        return d->currentStepIndex;
    }
    gotoStep(d->currentStepIndex + 1);
    return d->currentStepIndex;
}

void QtMaterialSteps::gotoStep(int idx)
{
    Q_D(QtMaterialSteps);
    d->gotoStep(idx);
}

int QtMaterialSteps::stepNum()
{
    Q_D(QtMaterialSteps);
    return d->stepBtns.size();
}

int QtMaterialSteps::currentStepIndex()
{
    Q_D(QtMaterialSteps);
    return d->currentStepIndex;
}

bool QtMaterialSteps::clickable()
{
    Q_D(QtMaterialSteps);
    return d->clickable;
}

void QtMaterialSteps::setClickable(bool clickable)
{
    Q_D(QtMaterialSteps);
    d->clickable = clickable;
    for(QPushButton *btn : d->stepBtns) {
        btn->setCheckable(clickable);
    }
}
