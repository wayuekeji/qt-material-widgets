# Qt Material Design Widgets

Qt Material Design Widgets is a C++ library providing Material Design components for Qt6/Qt5 applications. The project supports both CMake and qmake build systems, though CMake is strongly recommended.

**Always reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.**

## Common Tasks and File Locations

### Repository Structure
```
qt-material-widgets/
├── CMakeLists.txt          # Main CMake configuration
├── qt-material-widgets.pro # Main qmake configuration
├── components/             # Library source code
│   ├── CMakeLists.txt     # Component library CMake config
│   ├── components.pro     # Component library qmake config
│   └── *.cpp, *.h         # Material Design widget implementations
├── examples/               # Example application demonstrating all widgets
│   ├── CMakeLists.txt     # Examples CMake config
│   ├── examples.pro       # Examples qmake config
│   └── *settingseditor.* # Widget demo implementations
├── include/qmetarial/     # Public header files
└── build/                 # Generated build directory (CMake)
```