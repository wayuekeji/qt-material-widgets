cmake_minimum_required(VERSION 3.22)

project(
  QtMaterialWidgetsComponents
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core StateMachine)

option(QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK
       "Build the full Material icon resource pack" OFF)

include(sources.cmake)

set(RCC_FILES resources_core.qrc)
if(QTMATERIALWIDGETS_BUILD_FULL_ICON_PACK)
  list(APPEND RCC_FILES resources_full_icons.qrc)
endif()

set(QTMATERIALWIDGETS_CORE_TARGET QtMaterialWidgetsCore)
set(QTMATERIALWIDGETS_TARGET QtMaterialWidgets)
set(QTMATERIALWIDGETS_INSTALLED_HEADERS ${QTMATERIALWIDGETS_PUBLIC_HEADERS})
set(QTMATERIALWIDGETS_INSTALLED_LIB_HEADERS
    ${QTMATERIALWIDGETS_PUBLIC_LIB_HEADERS})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(QTMATERIALWIDGETS_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/QtMaterialWidgets")

list(REMOVE_ITEM QTMATERIALWIDGETS_INSTALLED_HEADERS
     "../include/qmetarial/qtmaterialcombobox.h"
     "../include/qmetarial/qtmateriallist.h"
     "../include/qmetarial/qtmateriallistitem.h"
     "../include/qmetarial/qtmaterialmenu.h"
     "../include/qmetarial/qtmaterialpaper.h"
     "../include/qmetarial/qtmaterialsteps.h"
     "../include/qmetarial/qtmaterialtable.h")

add_library(
  ${QTMATERIALWIDGETS_CORE_TARGET}
  STATIC
  ${QTMATERIALWIDGETS_CORE_SOURCES}
  ${QTMATERIALWIDGETS_CORE_PRIVATE_HEADERS}
  ${QTMATERIALWIDGETS_PUBLIC_LIB_HEADERS})

set_target_properties(${QTMATERIALWIDGETS_CORE_TARGET}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(
  ${QTMATERIALWIDGETS_TARGET}
  SHARED
  ${QTMATERIALWIDGETS_WIDGET_SOURCES}
  ${QTMATERIALWIDGETS_WIDGET_PRIVATE_HEADERS}
  ${QTMATERIALWIDGETS_PUBLIC_HEADERS}
  ${RCC_FILES})

add_library(QtMaterialWidgets::Widgets ALIAS ${QTMATERIALWIDGETS_TARGET})

target_compile_definitions(${QTMATERIALWIDGETS_CORE_TARGET}
                           PRIVATE QTMATERIALWIDGETS_LIBRARY=true)
target_compile_definitions(${QTMATERIALWIDGETS_TARGET}
                           PRIVATE QTMATERIALWIDGETS_LIBRARY=true)

target_link_libraries(
  ${QTMATERIALWIDGETS_CORE_TARGET}
  PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::StateMachine)

target_include_directories(
  ${QTMATERIALWIDGETS_CORE_TARGET}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qmetarial>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  ${QTMATERIALWIDGETS_TARGET}
  PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::StateMachine
  PRIVATE ${QTMATERIALWIDGETS_CORE_TARGET})

target_include_directories(
  ${QTMATERIALWIDGETS_TARGET}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/qmetarial>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qmetarial>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(
  ${QTMATERIALWIDGETS_TARGET}
  PROPERTIES
    EXPORT_NAME Widgets
    OUTPUT_NAME QtMaterialWidgets
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

install(FILES ${QTMATERIALWIDGETS_INSTALLED_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmetarial)

install(FILES ${QTMATERIALWIDGETS_INSTALLED_LIB_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qmetarial/lib)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QtMaterialWidgetsConfigVersion.cmake
  DESTINATION ${QTMATERIALWIDGETS_INSTALL_CMAKEDIR})

install(
  EXPORT QtMaterialWidgetsTargets
  FILE QtMaterialWidgetsTargets.cmake
  NAMESPACE QtMaterialWidgets::
  DESTINATION ${QTMATERIALWIDGETS_INSTALL_CMAKEDIR})
