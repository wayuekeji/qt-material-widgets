# Qt Material Design Desktop Widgets [![Language](https://img.shields.io/badge/language-c++-brightgreen.svg)]()

**YouTube** video preview [available here](http://www.youtube.com/watch?v=21UMeNVBPU4).

---

I've been using Qt for a while, the lack of UI framework is a big problem for me.

After building UI components from scratch for a while, I decided to try reusing other's projects, that is no piece of cake.

I found [qt-material-widgets](https://github.com/laserpants/qt-material-widgets), but sadly it seems to be no longer supported.

Pull requests from other developer, such as [move to cmake](https://github.com/laserpants/qt-material-widgets/pull/50) which inspired me on migrating this project from `qmake` to `CMake`, are not accepted anymore.

I'm very honored to try to take over the maintenance of this project, and welcome all pull requests and issues.

## Overview

The original project only supports the qmake build system on Linux platform.

The new project will support both qmake and CMake on as many platforms as possible, mainly Windows, Android ,Linux and MacOS.


## Usage

### use in your own project

#### CMake

1. clone this project

```
git clone https://github.com/Zhang-Tianxu/qt-material-widgets
```

2. create your widgets app with CMake build system

Create *Qt Widgets Application* with CMake project as normal

3. modify `CMakeLists.txt` of your app
    1. add *component* as subdirectory of your project
    ```CMake
    add_subdirectory(/path/to/qt-material-widgets/components/ ./components)
    ```
    2. add *include* and *link libraries*:
        - add `/path/to/qt-material-widgets/include/qmeterial/` into `target_include_directories` for headers
        - add `components` into `target_link_libraries` for `.lib`

Now you can use *qt-material-widgets*, all components list as follows:

#### qmake

1. clone this project

```
git clone https://github.com/Zhang-Tianxu/qt-material-widgets
```

2. create your widgets app with qmake build system

### example

1. clone this project

```
git clone https://github.com/Zhang-Tianxu/qt-material-widgets
```

2. open `CMakeLists.txt`/`qt-material-widgets.pro` in root directory of this repo by Qt Creator
3. select a build Kit and run


## progress

---

I've been using Qt for a while, the lack of UI framework is a big problem for me.

After building UI components from scratch for a while, I decided to try reusing other's projects, that is no piece of cake.

I found [qt-material-widgets](https://github.com/laserpants/qt-material-widgets), but sadly it seems to be no longer supported.

Pull requests from other developer, such as [move to cmake](https://github.com/laserpants/qt-material-widgets/pull/50) which inspired me on migrating this project from `qmake` to `CMake`, are not accepted anymore.

I'm very honored to try to take over the maintenance of this project, and welcome all pull requests and issues.

## Overview

The original project only supports the qmake build system on Linux platform.

The new project will support both qmake and CMake on as many platforms as possible, mainly Windows, Android ,Linux and MacOS.

## progress

<table>
  <tbody>
    <tr>
      <td colspan="2" align="center"></td>
    </tr>
    <tr>
      <td>
        App Bar
      </td>
      <td>
        <code>QtMaterialAppBar</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/appbar.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Auto Complete
      </td>
      <td>
        <code>QtMaterialAutoComplete</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/autocomplete.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Avatar
      </td>
      <td>
        <code>QtMaterialAvatar</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/avatar.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Badge
      </td>
      <td>
        <code>QtMaterialBadge</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/badge.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Check Box
      </td>
      <td>
        <code>QtMaterialCheckBox</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/checkbox.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Circular Progress
      </td>
      <td>
        <code>QtMaterialCircularProgress</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/circularprogress.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Dialog
      </td>
      <td>
        <code>QtMaterialDialog</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/dialog.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Drawer
      </td>
      <td>
        <code>QtMaterialDrawer</code>
      </td>
    </tr>
    <tr>
      <td colspan="2">
        <img src="gifs/drawer.gif" />
      </td>
    </tr>
    <tr>
      <td>
        FAB
      </td>
      <td>
        <code>QtMaterialFloatingActionButton</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/fab.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Flat Button
      </td>
      <td>
        <code>QtMaterialFlatButton</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/flatbutton.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Icon Button
      </td>
      <td>
        <code>QtMaterialIconButton</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/iconbutton.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Progress
      </td>
      <td>
        <code>QtMaterialProgress</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/progress.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Radio Button
      </td>
      <td>
        <code>QtMaterialRadioButton</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/radiobutton.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Raised Button
      </td>
      <td>
        <code>QtMaterialRaisedButton</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/raisedbutton.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Scroll Bar
      </td>
      <td>
        <code>QtMaterialScrollBar</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/scrollbar.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Slider
      </td>
      <td>
        <code>QtMaterialSlider</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/slider.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Snackbar
      </td>
      <td>
        <code>QtMaterialSnackBar</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/snackbar.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Tabs
      </td>
      <td>
        <code>QtMaterialTabs</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/tabs.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Text Field
      </td>
      <td>
        <code>QtMaterialTextField</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/textfield.gif" />
      </td>
    </tr>
    <tr>
      <td>
        Toggle
      </td>
      <td>
        <code>QtMaterialToggle</code>
      </td>
    </tr>
    <tr>
      <td colspan="2" align="center">
        <img src="gifs/toggle.gif" />
      </td>
    </tr>
  </tbody>
</table>

#### Implemented components

- [x] App Bar
- [x] Auto Complete
- [x] Avatar
- [x] Badge
- [x] Check Box
- [x] Circular Progress
- [x] Dialog
- [x] Drawer
- [x] Floating Action Button
- [x] Flat Button
- [x] Icon Button
- [x] Progress
- [x] Radio Button
- [x] Raised Button
- [x] Scroll Bar
- [x] Slider
- [x] Snackbar
- [x] Tabs
- [x] Text Field
- [x] Toggle

#### Work in progress

- [ ] Divider
- [ ] List
- [ ] List Item
- [ ] Menu
- [ ] Paper
- [ ] Snackbar Layout
- [ ] Table

#### Not implemented 

- [ ] Card
- [ ] Chips
- [ ] Discrete Slider
- [ ] Grid List
- [ ] Icon Menu
- [ ] Search Field
- [ ] Select Field
- [ ] Stepper
- [ ] Subheaders
- [ ] Toolbar

## About Android support

example can compile and run properly, but UI not fit to mobile.

<img style="width:400px;text-align:center;" src="https://github.com/Zhang-Tianxu/qt-material-widgets/assets/19359257/db116687-3dc3-445f-b41b-3e2594cf0d48" />

