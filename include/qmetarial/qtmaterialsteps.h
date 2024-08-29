#ifndef QTMATERIALSTEPS_H
#define QTMATERIALSTEPS_H

#include <QWidget>
#include <QPushButton>
#include "components_global.h"

class QtMaterialStepsPrivate;
class QtMaterialSteps;

class COMPONENTS_EXPORT QtMaterialSteps : public QWidget
{
    Q_OBJECT
public:
    explicit QtMaterialSteps(QWidget *parent = nullptr);
    ~QtMaterialSteps();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    /*
     * 增加新的步骤按钮，例如:
     *   topStep->addNewStepBtn("受试者信息录入", QRect(0, 0, 400, 30));
     *   topStep->addNewStepBtn("参数选择", QRect(350, 0, 400, 30));
     *   topStep->addNewStepBtn("动作引导", QRect(700, 0, 400, 30));
     * 其中QRect代表了（x位移, y位移, 宽度, 高度)
     * 目前的实现方式，要求由左向右添加按钮，如果顺序错误会导致布局错误。另外如果按钮高度不同，比最后一个按钮高度大的会被截断
     * TODO：后续修复这个问题，思路是记录最右值和最下值
     */
    void addNewStepBtn(QString title, QRect geo);

    // 步骤数量
    int stepNum();
    int currentStepIndex();

    bool clickable();
    void setClickable(bool clickable);

public slots:
    int nextStep(); // 返回跳转后的index
    void gotoStep(int idx);

signals:
    void stepChanged(int idx);

protected:
    const QScopedPointer<QtMaterialStepsPrivate> d_ptr;

private:

private:
    Q_DISABLE_COPY(QtMaterialSteps);
    Q_DECLARE_PRIVATE(QtMaterialSteps);

};

#endif  // QTMATERIALSTEPS_H
