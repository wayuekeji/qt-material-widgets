#ifndef QTMATERIALSTEPS_P_H
#define QTMATERIALSTEPS_P_H

#include "lib/qtmaterialtheme.h"
#include <QtGlobal>
#include <QPushButton>

class QtMaterialSteps;

class QtMaterialStepsPrivate
{
    Q_DISABLE_COPY(QtMaterialStepsPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSteps)

public:
    QtMaterialStepsPrivate(QtMaterialSteps *q);
    ~QtMaterialStepsPrivate();

    void init();
    void stepBtnClicked(int index);
    void gotoStep(int idx);

    QWidget *container;
    std::vector<QPushButton*> stepBtns;
    int currentStepIndex;
    bool clickable;
    QtMaterialSteps *const q_ptr;
    QColor backgroundColor;
    QColor textColor;
};

#endif  // QTMATERIALSTEPS_P_H
