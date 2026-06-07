#include "mainwindow.h"
#include "demopageregistry.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    widget->setMaximumHeight(800);
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);

    layout->setStretch(1, 2);

    setCentralWidget(widget);

    const QVector<DemoPageDefinition> pages = demoPageDefinitions();
    for (const DemoPageDefinition &page : pages) {
        list->addItem(page.title);
        stack->addWidget(page.factory());
    }

    QObject::connect(list, &QListWidget::currentRowChanged, [stack](int row) {
        if (row >= 0 && row < stack->count()) {
            stack->setCurrentIndex(row);
        }
    });

    list->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
}
