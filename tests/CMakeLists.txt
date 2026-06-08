cmake_minimum_required(VERSION 3.22)

project(
  QtMaterialWidgetsTests
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

add_executable(qtmaterialwidgets_smoke_test qtmaterialwidgets_smoke_test.cpp)

target_link_libraries(
  qtmaterialwidgets_smoke_test
  PRIVATE QtMaterialWidgets::Widgets Qt6::Test Qt6::Widgets)

if(WIN32)
  add_custom_command(
    TARGET qtmaterialwidgets_smoke_test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:QtMaterialWidgets>
            $<TARGET_FILE_DIR:qtmaterialwidgets_smoke_test>)
endif()

add_test(NAME qtmaterialwidgets_smoke_test
         COMMAND qtmaterialwidgets_smoke_test)

set_tests_properties(
  qtmaterialwidgets_smoke_test
  PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    ENVIRONMENT_MODIFICATION
    "PATH=path_list_prepend:$<TARGET_FILE_DIR:Qt6::Core>")
