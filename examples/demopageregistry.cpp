#include "demopageregistry.h"

#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "comboboxsettingseditor.h"
#include "dialogsettingseditor.h"
#include "dividersettingseditor.h"
#include "drawersettingseditor.h"
#include "fabsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "menusettingseditor.h"
#include "progresssettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "slidersettingseditor.h"
#include "snackbarsettingseditor.h"
#include "stepssettingseditor.h"
#include "tabssettingseditor.h"
#include "textfieldsettingseditor.h"
#include "togglesettingseditor.h"

QVector<DemoPageDefinition> demoPageDefinitions()
{
    return {
        {"App Bar", [] { return new AppBarSettingsEditor; }},
        {"Auto Complete", [] { return new AutoCompleteSettingsEditor; }},
        {"Avatar", [] { return new AvatarSettingsEditor; }},
        {"Badge", [] { return new BadgeSettingsEditor; }},
        {"Checkbox", [] { return new CheckBoxSettingsEditor; }},
        {"Circular Progress", [] { return new CircularProgressSettingsEditor; }},
        {"ComboBox", [] { return new ComboBoxSettingsEditor; }},
        {"Dialog", [] { return new DialogSettingsEditor; }},
        {"Divider", [] { return new DividerSettingsEditor; }},
        {"Drawer", [] { return new DrawerSettingsEditor; }},
        {"Floating Action Button", [] { return new FloatingActionButtonSettingsEditor; }},
        {"Flat Button", [] { return new FlatButtonSettingsEditor; }},
        {"Icon Button", [] { return new IconButtonSettingsEditor; }},
        {"Menu", [] { return new MenuSettingsEditor; }},
        {"Progress", [] { return new ProgressSettingsEditor; }},
        {"Radio Button", [] { return new RadioButtonSettingsEditor; }},
        {"Raised Button", [] { return new RaisedButtonSettingsEditor; }},
        {"ScrollBar", [] { return new ScrollBarSettingsEditor; }},
        {"Slider", [] { return new SliderSettingsEditor; }},
        {"Snackbar", [] { return new SnackbarSettingsEditor; }},
        {"Steps", [] { return new stepssettingseditor; }},
        {"Tabs", [] { return new TabsSettingsEditor; }},
        {"Text Field", [] { return new TextFieldSettingsEditor; }},
        {"Toggle", [] { return new ToggleSettingsEditor; }},
    };
}
