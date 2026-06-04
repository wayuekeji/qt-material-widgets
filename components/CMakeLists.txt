cmake_minimum_required(VERSION 3.22)

project(
  components
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core StateMachine)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core StateMachine)

file(GLOB THELIB "materiallib/*") # 利用正则表达式找出源文件
file(GLOB COMPONENTSHEADER "*.h")
file(GLOB COMPONENTSSOURCE "*.cpp")
file(GLOB HEADER "../include/qmetarial/*.h")
file(GLOB HEADER2 "../include/qmetarial/lib/*.h")

set(RCC_FILES resources.qrc)
set(QTMATERIALWIDGETS_CORE_TARGET QtMaterialWidgetsCore)
set(QTMATERIALWIDGETS_TARGET QtMaterialWidgets)
set(QTMATERIALWIDGETS_INSTALLED_HEADERS ${HEADER})
set(QTMATERIALWIDGETS_INSTALLED_LIB_HEADERS ${HEADER2})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(QTMATERIALWIDGETS_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/QtMaterialWidgets")

list(REMOVE_ITEM QTMATERIALWIDGETS_INSTALLED_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial/qtmateriallist.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial/qtmateriallistitem.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial/qtmaterialpaper.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial/qtmaterialtable.h")

add_library(
  ${QTMATERIALWIDGETS_CORE_TARGET}
  STATIC
  ${THELIB}
  ${RCC_FILES}
  ${HEADER2})

set_target_properties(${QTMATERIALWIDGETS_CORE_TARGET}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(
  ${QTMATERIALWIDGETS_TARGET}
  SHARED
  ${COMPONENTSHEADER}
  ${COMPONENTSSOURCE}
  ${HEADER})

add_library(QtMaterialWidgets::Widgets ALIAS ${QTMATERIALWIDGETS_TARGET})

target_compile_definitions(${QTMATERIALWIDGETS_CORE_TARGET}
                           PRIVATE COMPONENTS_LIBRARY=true)
target_compile_definitions(${QTMATERIALWIDGETS_TARGET}
                           PRIVATE COMPONENTS_LIBRARY=true)

target_link_libraries(${QTMATERIALWIDGETS_CORE_TARGET} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::StateMachine
)

target_include_directories(
  ${QTMATERIALWIDGETS_CORE_TARGET}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qmetarial>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  ${QTMATERIALWIDGETS_TARGET}
  PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::StateMachine
  PRIVATE
    ${QTMATERIALWIDGETS_CORE_TARGET})

target_include_directories(
  ${QTMATERIALWIDGETS_TARGET}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qmetarial>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(
  ${QTMATERIALWIDGETS_TARGET}
  PROPERTIES
    EXPORT_NAME Widgets
    OUTPUT_NAME components
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/QtMaterialWidgetsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfig.cmake
  INSTALL_DESTINATION ${QTMATERIALWIDGETS_INSTALL_CMAKEDIR})

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  TARGETS ${QTMATERIALWIDGETS_TARGET}
  EXPORT QtMaterialWidgetsTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmetarial)

install(
  FILES
    ${QTMATERIALWIDGETS_INSTALLED_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmetarial)

install(
  FILES ${QTMATERIALWIDGETS_INSTALLED_LIB_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmetarial/lib)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfigVersion.cmake
  DESTINATION ${QTMATERIALWIDGETS_INSTALL_CMAKEDIR})

install(
  EXPORT QtMaterialWidgetsTargets
  FILE QtMaterialWidgetsTargets.cmake
  NAMESPACE QtMaterialWidgets::
  DESTINATION ${QTMATERIALWIDGETS_INSTALL_CMAKEDIR})
