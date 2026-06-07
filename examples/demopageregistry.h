#ifndef DEMOPAGEREGISTRY_H
#define DEMOPAGEREGISTRY_H

#include <QString>
#include <QVector>
#include <functional>

class QWidget;

struct DemoPageDefinition
{
    QString title;
    std::function<QWidget *()> factory;
};

QVector<DemoPageDefinition> demoPageDefinitions();

#endif // DEMOPAGEREGISTRY_H
