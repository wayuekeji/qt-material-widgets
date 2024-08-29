#ifndef QTMATERIALSTATETRANSITION_H
#define QTMATERIALSTATETRANSITION_H

#include "lib/qtmaterialstatetransitionevent.h"
#include "components_global.h"
#include <QAbstractTransition>

class COMPONENTS_EXPORT QtMaterialStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    QtMaterialStateTransition(QtMaterialStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    QtMaterialStateTransitionType m_type;
};

#endif  // QTMATERIALSTATETRANSITION_H
