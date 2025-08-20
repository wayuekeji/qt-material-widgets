# Visual Studio Code Integration for qt-material-widgets

This directory contains VS Code configuration files to enable building, debugging, and developing the qt-material-widgets project in Visual Studio Code on Windows, **Linux and MacOS not supported yet.**

## Prerequisites

1. **Visual Studio Code** with the following extensions:
   - C/C++ (ms-vscode.cpptools)
   - CMake Tools (ms-vscode.cmake-tools)

2. **Qt 6.x** installed (Qt5 also supported)

3. **CMake** (version 3.22 or later)

4. **Build Tools**:
   - Windows: Visual Studio Build Tools or Visual Studio Community

## Environment Setup

Set the following environment variables:

### For all platforms:
- `CMAKE_PREFIX_PATH`: Path to your Qt installation

### Examples:

**Windows:**
```batch
set CMAKE_PREFIX_PATH=C:\Qt\6.6.3\msvc2019_64
```

## Usage

1. Open the project root directory in VS Code
2. Press `Ctrl+Shift+P` and run "Tasks: Run Task" 
3. Select "cmake-configure" (Windows)
4. Press `F5` to build and run the examples application

## Available Tasks

- **cmake-configure**: Configure CMake with Visual Studio generator (Windows)
- **cmake-build-debug**: Build in Debug mode

## Debug Configurations

- **Launch qt-material-widgets (Windows Debug)**: Launch in Debug mode on Windows

## IntelliSense Configurations

The project includes platform-specific IntelliSense configurations:
- **qt-material-widgets (Windows)**: MSVC compiler support

## File Structure

- `launch.json`: Debug configurations for all platforms
- `tasks.json`: Build and configure tasks
- `settings.json`: Workspace settings
- `extensions.json`: Recommended VS Code extensions
- `README.md`: This documentation

## Troubleshooting

1. **Build errors**: Ensure CMAKE_PREFIX_PATH points to your Qt installation
2. **Executable not found**: Make sure the build completed successfully
3. **Missing Qt libraries**: 
   - Windows: Ensure Qt's bin directory is in your PATH
## Platform-Specific Notes

### Windows
- Uses Visual Studio generator by default
- Executable will be in `build/examples/Debug/examples.exe`
- Requires Visual Studio Build Tools or Visual Studio Community