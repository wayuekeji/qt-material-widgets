## Way to use this project

The primary integration path is the exported CMake package:

```cmake
find_package(QtMaterialWidgets CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE QtMaterialWidgets::Widgets)
```

Use `CMAKE_PREFIX_PATH` to point the consumer project at the install prefix when the package is not installed in a default CMake search location.

The historical approach of manually adding include directories and linking `.lib` or `.so` files directly is no longer the recommended path. Keep it only as a fallback for local debugging.

The minimal installed-package consumer is stored in `examples/consumer`.
