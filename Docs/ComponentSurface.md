# Component Surface

This document defines the current delivery status of public widget modules.

Only `stable` widgets are installed by default as part of the package Interface. `experimental` and `stub` widgets may remain in the source tree and demo application, but they are not part of the default installed Interface.

## Stable Theme Interface

The installed package exposes typed theme keys through `Material::ThemeColor`. New code should prefer the typed overloads:

```cpp
QtMaterialTheme theme;
theme.setColor(Material::ThemeColor::Accent1, QColor("#ff4081"));

QColor border = QtMaterialStyle::instance().themeColor(Material::ThemeColor::Border);
```

The legacy string-based theme methods remain available for compatibility and custom keys.

## Resource Packs

The default CMake build embeds only the core resource pack:

- Roboto fonts used by `QtMaterialStyle`.
- Checkbox and radio-button icons required by stable checkable widgets.
- `message`, `menu`, and `star` icons used by the current demo smoke surface.
- The combobox arrow used by source-level experimental builds.

The full Material icon catalog is optional. Downstream consumers that call `QtMaterialTheme::icon(category, icon)` for arbitrary Material icons must configure the package with:

```cmake
-DQTMATERIALWIDGETS_BUILD_FULL_ICON_PACK=ON
```

## Stable

These widgets are installed by default:

- `QtMaterialAppBar`
- `QtMaterialAutoComplete`
- `QtMaterialAvatar`
- `QtMaterialBadge`
- `QtMaterialCheckBox`
- `QtMaterialCircularProgress`
- `QtMaterialDialog`
- `QtMaterialDivider`
- `QtMaterialDrawer`
- `QtMaterialFloatingActionButton`
- `QtMaterialFlatButton`
- `QtMaterialIconButton`
- `QtMaterialProgress`
- `QtMaterialRadioButton`
- `QtMaterialRaisedButton`
- `QtMaterialScrollBar`
- `QtMaterialSlider`
- `QtMaterialSnackbar`
- `QtMaterialTabs`
- `QtMaterialTextField`
- `QtMaterialToggle`

## Experimental

These widgets are available in source form for development and demos, but are not installed by default:

- `QtMaterialComboBox`
- `QtMaterialSteps`

## Stub

These widgets have a public source-level shell, but the Interface is not complete enough for installation:

- `QtMaterialMenu`
- `QtMaterialList`
- `QtMaterialListItem`
- `QtMaterialPaper`
- `QtMaterialTable`

## Not Implemented

These widgets are roadmap items only:

- Card
- Chips
- Discrete Slider
- Grid List
- Icon Menu
- Search Field
- Select Field
- Stepper
- Subheaders
- Toolbar
- Snackbar Layout
