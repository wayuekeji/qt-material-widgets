# Using GitHub Release Archives

This project publishes GitHub Release archives for the supported desktop CMake package path.

The release archives are CMake install prefixes. They are not full application installers and they do not bundle the Qt runtime for your application.

## Pick the Correct Asset

Download the asset that matches your target platform and toolchain:

| Asset suffix | Target |
| --- | --- |
| `windows-x64.zip` | Windows x64, MSVC-compatible Qt 6 build |
| `ubuntu-x64.zip` | Ubuntu x64, GCC-compatible Qt 6 build |
| `macos-x64.zip` | macOS Intel x64, Clang-compatible Qt 6 build |

Example asset names:

```text
qt-material-widgets-v0.2.0-windows-x64.zip
qt-material-widgets-v0.2.0-ubuntu-x64.zip
qt-material-widgets-v0.2.0-macos-x64.zip
```

Use the same platform, architecture, compiler ABI, and compatible Qt major version in your application. The current release workflow builds with Qt 6.6.3.

## Extract the Archive

Extract the archive to a stable dependency location.

After extraction, use the directory that contains this file as the package prefix:

```text
lib/cmake/QtMaterialWidgets/QtMaterialWidgetsConfig.cmake
```

For example:

```text
third_party/qt-material-widgets-v0.2.0-windows-x64/
  bin/
  include/
  lib/
    cmake/
      QtMaterialWidgets/
        QtMaterialWidgetsConfig.cmake
```

In this example, pass `third_party/qt-material-widgets-v0.2.0-windows-x64` to `CMAKE_PREFIX_PATH`.

## Consume From CMake

Your application must find Qt first through its normal Qt installation or toolchain setup. Then point CMake at the extracted Qt Material Widgets prefix.

Configure your application:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="/path/to/qt-material-widgets-prefix;/path/to/qt"
cmake --build build --config Release
```

On single-config generators such as Ninja or Unix Makefiles, include `-DCMAKE_BUILD_TYPE=Release` if needed:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/path/to/qt-material-widgets-prefix;/path/to/qt"
```

Use the exported package target in your `CMakeLists.txt`:

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(QtMaterialWidgets CONFIG REQUIRED)

target_link_libraries(my_app PRIVATE
  Qt6::Widgets
  QtMaterialWidgets::Widgets
)
```

Do not manually add release archive `include` or `lib` directories when using the supported CMake package path. The imported target carries the package metadata.

## Runtime Deployment

The release archive provides the Qt Material Widgets library install output. It does not deploy Qt runtime libraries for your application.

You are responsible for deploying:

- Qt runtime libraries required by your application.
- The Qt platform plugin, such as `qwindows`, `xcb`, or `cocoa`.
- Any other runtime dependencies required by your own executable.
- The Qt Material Widgets shared library at runtime.

Typical handling:

| Platform | Runtime handling |
| --- | --- |
| Windows | Put the package `bin` directory on `PATH`, or copy the required DLLs next to your executable. Deploy Qt with `windeployqt` or your own installer. |
| Linux | Put the package `lib` directory on `LD_LIBRARY_PATH`, install to a system prefix, or configure your application rpath. Deploy Qt according to your distribution strategy. |
| macOS | Put the package library where your app bundle can load it, or configure install names/rpaths. Deploy Qt with `macdeployqt` or your own bundle process. |

## Minimal Consumer Check

This repository contains a minimal installed-package consumer in `examples/consumer`.

After extracting a release archive, you can validate the package with:

```bash
cmake -S examples/consumer -B build-consumer -DCMAKE_PREFIX_PATH="/path/to/qt-material-widgets-prefix;/path/to/qt"
cmake --build build-consumer --config Release
```

This is the same consumption model used by CI and release packaging.

## Troubleshooting

### CMake cannot find QtMaterialWidgets

Check that `CMAKE_PREFIX_PATH` points to the prefix containing:

```text
lib/cmake/QtMaterialWidgets/QtMaterialWidgetsConfig.cmake
```

Do not point `CMAKE_PREFIX_PATH` directly at `lib/cmake/QtMaterialWidgets`.

### CMake finds QtMaterialWidgets but cannot find Qt6

Install a compatible Qt 6 build and add the Qt installation prefix to `CMAKE_PREFIX_PATH`, or set `Qt6_DIR` to the directory containing `Qt6Config.cmake`.

### Windows link or runtime failures

Use a Qt build with a compatible MSVC x64 ABI. The Windows release package is built against the MSVC Qt archive used by CI.

At runtime, ensure the Qt Material Widgets DLL and required Qt DLLs are discoverable through `PATH` or are placed next to your executable.

### Linux or macOS runtime loader failures

Ensure the Qt Material Widgets shared library and Qt runtime libraries are discoverable by the platform loader. Use `LD_LIBRARY_PATH`, rpath, install names, app bundle deployment, or system installation according to your packaging model.

### The archive looks like an install directory, not an SDK installer

That is expected. Release assets are generated from `cmake --install` output and are meant to be consumed through CMake package discovery.
