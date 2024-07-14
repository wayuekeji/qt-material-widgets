#ifndef STEPSSETTINGSEDITOR_H
#define STEPSSETTINGSEDITOR_H

#include <QWidget>
#include "ui_stepssettingsform.h"

class QtMaterialSteps;

class stepssettingseditor : public QWidget
{
    Q_OBJECT
public:
    explicit stepssettingseditor(QWidget *parent = nullptr);
    ~stepssettingseditor();

signals:

private:
    Ui::StepsSettingsForm *const ui;
    QtMaterialSteps *const m_steps;
};

#endif  // STEPSSETTINGSEDITOR_H
