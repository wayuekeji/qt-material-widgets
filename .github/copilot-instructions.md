# Qt Material Design Widgets

Qt Material Design Widgets is a C++17 Qt Widgets library providing Material Design inspired components, theme helpers, resources, examples, and CMake package integration.

CMake is the supported build, package, install, test, and consumer integration path. qmake files are legacy and unverified unless a specific change explicitly adds qmake validation.

**Always reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.**

## Common Tasks and File Locations

### Repository Structure
```
qt-material-widgets/
├── CMakeLists.txt              # Main CMake configuration
├── qt-material-widgets.pro     # Legacy qmake entry point
├── CONTEXT.md                  # Project architecture context
├── Docs/
│   ├── ArchitectureOptimizationReport.md
│   └── ComponentSurface.md
├── docs/adr/                   # Architecture decision records
├── openspec/changes/           # Active OpenSpec changes
├── components/                 # Library implementation and resources
│   ├── CMakeLists.txt
│   ├── sources.cmake           # Explicit library source manifest
│   ├── resources_core.qrc      # Default resource pack
│   ├── resources_full_icons.qrc # Optional full icon pack
│   └── *.cpp, *.h
├── examples/                   # Example application and consumer smoke project
│   ├── CMakeLists.txt
│   ├── sources.cmake
│   ├── demopageregistry.*
│   └── consumer/
├── include/qmetarial/          # Public installed headers
└── tests/                      # QTest/CTest smoke tests
```

## Verification Gates

- `openspec validate --all --strict`
- CMake Release build of `QtMaterialWidgets`
- `ctest --output-on-failure` with `BUILD_TESTING=ON`
- `cmake --install` followed by `examples/consumer` build using `CMAKE_PREFIX_PATH`
- Examples Release build when demo behavior changes
- GitHub Actions CI for Windows/Linux CMake Release build, CTest, examples, install, and consumer build
