cmake_minimum_required(VERSION 3.5)

project(
  examples
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPONENTS_LIBS
    ${CMAKE_BINARY_DIR}/components/components.lib # path to .lib
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB HEADER "*.h")
file(GLOB RSOURCE "*.cpp")
file(GLOB UI "*.ui")

set(RCC_FILES examples.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${HEADER}
        ${RSOURCE}
        ${UI}
        ${RCC_FILES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
                ${HEADER}
                ${RSOURCE}
                ${UI}
                ${RCC_FILES}
        )
    else()
        add_executable(${PROJECT_NAME}
                ${HEADER}
                ${RSOURCE}
                ${UI}
                ${RCC_FILES}
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ../include/qmetarial/)
target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Core
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${COMPONENTS_LIBS}
)

set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  ${BUNDLE_ID_OPTION}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING
  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
