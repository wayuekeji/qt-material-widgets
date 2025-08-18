# Qt Material Design Widgets

Qt Material Design Widgets is a C++ library providing Material Design components for Qt6/Qt5 applications. The project supports both CMake and qmake build systems, though CMake is strongly recommended.

**Always reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.**

## Working Effectively

### Prerequisites and Dependencies
- Install required system dependencies:
  ```bash
  sudo apt update
  sudo apt install -y qt6-base-dev qt6-tools-dev qt6-tools-dev-tools build-essential
  sudo apt install -y libqt6statemachine6  # Runtime library (development headers not available in Ubuntu)
  ```
- **CRITICAL LIMITATION**: Qt StateMachine development headers are not available in Ubuntu repositories. The project requires manual workarounds to build.

### Build with CMake (Recommended)
- **ALWAYS** use CMake over qmake for this project. The README explicitly states qmake has "strange problems".
- **NEVER CANCEL**: Build takes 25-35 seconds initially, 8-10 seconds for incremental builds. Set timeout to 120+ seconds.

#### Bootstrap and Build Commands:
```bash
# Create build directory
mkdir -p build && cd build

# Configure (takes ~0.4 seconds)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build (takes 25-35 seconds full build, NEVER CANCEL)
make -j$(nproc)
```

#### Known Issues and Workarounds:
- **StateMachine Module Missing**: Ubuntu packages lack Qt StateMachine development headers
- **Workaround Required**: Must temporarily comment out StateMachine references in CMakeLists.txt files:
  ```cmake
  # In components/CMakeLists.txt, change:
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core StateMachine)
  # To:
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
  
  # And comment out:
  # Qt${QT_VERSION_MAJOR}::StateMachine
  ```
- **Qt5/Qt6 Lambda Compatibility**: May need to fix lambda syntax in examples for Qt5:
  ```cpp
  // Change from:
  connect(ui->fontSizeDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [=](double value){
  // To:
  connect(ui->fontSizeDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value){
  ```

### Build with qmake (Limited Support)
- **NOT RECOMMENDED**: Has known linking issues and strange behaviors
- Configuration: `qmake6 qt-material-widgets.pro` (takes ~0.03 seconds)
- Build: `make -j$(nproc)` (takes 26-30 seconds, NEVER CANCEL)
- **ISSUE**: Examples often fail to link with components library

### Run and Test
- **Components Library**: Successfully builds as `libcomponents.so` (~2.1MB)
- **Example Application**: May have linking issues due to Qt5/Qt6 MOC compatibility
- **Library-only build**: `make components -j$(nproc)` (recommended, takes ~0.1 seconds)
- **Testing library build**:
  ```bash
  # Verify library was built successfully
  ls -la build/components/libcomponents.so
  ```
- **Expected behavior**: Library builds without errors, ready for integration

## Validation
- **ALWAYS** build the components library as the primary deliverable: `make components -j$(nproc)`
- **ALWAYS** verify the library builds successfully: `ls -la build/components/libcomponents.so`
- **Library validation**: Check that `libcomponents.so` exists (~2.1MB) in `build/components/`
- **Build time expectations**: 
  - Clean CMake build: 25-35 seconds for full build, 20-25 seconds for components only (NEVER CANCEL - set 120+ second timeout)
  - Incremental components build: <1 second
  - Configuration: <1 second
- **NOTE**: Examples may fail to build due to Qt5/Qt6 MOC compatibility issues, but the core library builds successfully

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

### Key Files to Monitor
- **Always check** `components/CMakeLists.txt` after modifying build configuration
- **Always verify** `build/components/libcomponents.so` exists after building
- **Always test** `build/examples/examples` runs without crashes

### Build Artifacts
- **Debug Mode**: Not recommended due to Qt5/Qt6 MOC compatibility issues
- **Release Mode**: Fully functional, recommended for all development
- **Output Library**: `build/components/libcomponents.so` (~2.5MB)
- **Example Binary**: `build/examples/examples` (~1.2MB)

## Troubleshooting

### StateMachine Issues
- **Error**: `Could not find Qt6StateMachine` or `Unknown module(s) in QT: statemachine`
- **Solution**: Temporarily comment out StateMachine dependencies as shown above
- **Root cause**: Ubuntu Qt packages don't include StateMachine development headers

### Build Failures
- **Clean and retry**: `rm -rf build && mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j$(nproc)`
- **qmake issues**: Switch to CMake build system
- **MOC version conflicts**: Use Release mode, avoid Debug mode

### Runtime Issues
- **No display available**: Use `QT_QPA_PLATFORM=offscreen` for headless testing
- **Missing dependencies**: Ensure all Qt6 base development packages are installed

## Development Workflow
1. **Always** start with CMake Release build
2. **Always** apply StateMachine workarounds before building
3. **Always** build the components library as primary target: `make components -j$(nproc)`
4. **Always** verify library output: `ls -la build/components/libcomponents.so`
5. **Never** cancel builds - components build completes in under 25 seconds
6. **Always** validate library exists before considering the build successful

## Performance Notes
- **Components library build**: 20-25 seconds (clean), <1 second (incremental)
- **Full project build**: 25-35 seconds (may fail on examples due to MOC issues)
- **Configuration**: <1 second
- **Primary deliverable**: `libcomponents.so` library (~2.1MB)