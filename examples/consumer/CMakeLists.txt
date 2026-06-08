cmake_minimum_required(VERSION 3.22)

project(
  qt-material-widgets-consumer
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(QtMaterialWidgets CONFIG REQUIRED)

add_executable(qt-material-widgets-consumer main.cpp)

target_link_libraries(qt-material-widgets-consumer PRIVATE
  QtMaterialWidgets::Widgets
  Qt6::Widgets)
