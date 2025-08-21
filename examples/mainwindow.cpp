#include "mainwindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "fabsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "progresssettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "slidersettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "textfieldsettingseditor.h"
#include "tabssettingseditor.h"
#include "stepssettingseditor.h"
#include "snackbarsettingseditor.h"
#include "dialogsettingseditor.h"
#include "drawersettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "menusettingseditor.h"
#include "comboboxsettingseditor.h"
#include "dividersettingseditor.h"
#include <QMap>

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

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    stepssettingseditor *steps = new stepssettingseditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    ComboBoxSettingsEditor *combobox = new ComboBoxSettingsEditor;
    DividerSettingsEditor *divider = new DividerSettingsEditor;

    QMap<QString, QWidget*> pageMap = {
        {"App Bar", appBar},
        {"Auto Complete", autocomplete},
        {"Avatar", avatar},
        {"Badge", badge},
        {"Checkbox", checkbox},
        {"Circular Progress", circularProgress},
        {"ComboBox", combobox},
        {"Dialog", dialog},
        {"Divider", divider},
        {"Drawer", drawer},
        {"Floating Action Button", fab},
        {"Flat Button", flatButton},
        {"Icon Button", iconButton},
        {"Menu", menu},
        {"Progress", progress},
        {"Radio Button", radioButton},
        {"Raised Button", raisedButton},
        {"ScrollBar", scrollBar},
        {"Slider", slider},
        {"Snackbar", snackbar},
        {"Tabs", tabs},
        {"Steps", steps},
        {"Text Field", textField},
        {"Toggle", toggle}
    };

    for (auto it = pageMap.begin(); it != pageMap.end(); ++it) {
        list->addItem(it.key());
        stack->addWidget(it.value());
    }

    list->setCurrentRow(0);

    QObject::connect(list, &QListWidget::currentTextChanged, [=](const QString &text){
        QWidget *w = pageMap.value(text, nullptr);
        if (w) stack->setCurrentWidget(w);
    });
}

MainWindow::~MainWindow()
{
}
