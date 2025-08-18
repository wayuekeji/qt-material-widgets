# Visual Studio Code Integration for qt-material-widgets

This directory contains VS Code configuration files to enable building, debugging, and developing the qt-material-widgets project in Visual Studio Code across Windows, Linux, and macOS.

## Prerequisites

1. **Visual Studio Code** with the following extensions:
   - C/C++ (ms-vscode.cpptools)
   - CMake Tools (ms-vscode.cmake-tools)

2. **Qt 6.x** installed (Qt5 also supported)

3. **CMake** (version 3.22 or later)

4. **Build Tools**:
   - Windows: Visual Studio Build Tools or Visual Studio Community
   - Linux: GCC and build-essential
   - macOS: Xcode Command Line Tools

## Environment Setup

Set the following environment variables:

### For all platforms:
- `CMAKE_PREFIX_PATH`: Path to your Qt installation

### Examples:

**Windows:**
```batch
set CMAKE_PREFIX_PATH=C:\Qt\6.6.3\msvc2019_64
```

**Linux:**
```bash
export CMAKE_PREFIX_PATH=/opt/Qt/6.6.3/gcc_64
# or
export CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

**macOS:**
```bash
export CMAKE_PREFIX_PATH=/Users/$(whoami)/Qt/6.6.3/macos
```

## Usage

1. Open the project root directory in VS Code
2. Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on macOS) and run "Tasks: Run Task" 
3. Select "cmake-configure" (Windows) or "cmake-configure-ninja" (Linux/macOS)
4. Press `F5` to build and run the examples application

## Available Tasks

- **cmake-configure**: Configure CMake with Visual Studio generator (Windows)
- **cmake-configure-ninja**: Configure CMake with Ninja generator (Linux/macOS)
- **cmake-build-dev**: Build in RelWithDebInfo mode (default, Windows)
- **cmake-build-dev-ninja**: Build using Ninja (Linux/macOS)
- **cmake-build-debug**: Build in Debug mode
- **cmake-build-release**: Build in Release mode
- **cmake-clean**: Clean build artifacts

## Debug Configurations

- **Launch qt-material-widgets (Windows)**: Launch in RelWithDebInfo mode on Windows
- **Launch qt-material-widgets (Windows Debug)**: Launch in Debug mode on Windows
- **Launch qt-material-widgets (Linux/macOS)**: Launch on Linux or macOS with GDB support

## IntelliSense Configurations

The project includes platform-specific IntelliSense configurations:
- **qt-material-widgets (Windows)**: MSVC compiler support
- **qt-material-widgets (Linux)**: GCC compiler support
- **qt-material-widgets (macOS)**: Clang compiler support

## File Structure

- `launch.json`: Debug configurations for all platforms
- `tasks.json`: Build and configure tasks
- `c_cpp_properties.json`: Platform-specific IntelliSense configuration
- `settings.json`: Workspace settings
- `extensions.json`: Recommended VS Code extensions
- `README.md`: This documentation

## Troubleshooting

1. **Build errors**: Ensure CMAKE_PREFIX_PATH points to your Qt installation
2. **Executable not found**: Make sure the build completed successfully
3. **Missing Qt libraries**: 
   - Windows: Ensure Qt's bin directory is in your PATH
   - Linux: Check LD_LIBRARY_PATH includes Qt lib directory
   - macOS: Verify Qt framework installation
4. **IntelliSense issues**: Check that compile_commands.json is generated in the build directory
5. **Task not found**: Select the correct configuration for your platform in the C/C++ extension

## Platform-Specific Notes

### Windows
- Uses Visual Studio generator by default
- Executable will be in `build/examples/RelWithDebInfo/examples.exe` or `build/examples/Debug/examples.exe`
- Requires Visual Studio Build Tools or Visual Studio Community

### Linux
- Uses Ninja generator by default
- Executable will be in `build/examples/examples`
- Make sure to install Qt development packages (e.g., `qt6-base-dev` on Ubuntu)

### macOS
- Uses Ninja generator by default
- Executable will be in `build/examples/examples`
- Install Qt via Homebrew (`brew install qt@6`) or Qt installer