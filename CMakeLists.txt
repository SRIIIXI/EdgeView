cmake_minimum_required(VERSION 3.16)

project(EdgeView VERSION 3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_SUFFIX "")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(UNIX AND NOT APPLE)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
        message("-- Configuring for Android ...")
        set(ANDROID_LINUX TRUE)
    else()
        message("-- Configuring for Linux ...")
        set(GNU_LINUX TRUE)
    endif()
endif()

if(UNIX AND APPLE)
    message("-- Configuring for Darwin (MacOS, iOS) ...")
    set(MACOS TRUE)
    set(IOS TRUE)
endif()

if(WIN32)
    message("-- Configuring for Windows ...")
    set(DARWIN TRUE)
endif()

find_package(Qt6 6 REQUIRED COMPONENTS Quick Core Qml Network)
qt_standard_project_setup(REQUIRES 6)

set(SOURCE_DIR ./src)
set(HEADER_DIR ./include)
include_directories(${PROJECT_HEADER_DIR} ./include ./darwin)

set(SOURCES
${SOURCES}
${SOURCE_DIR}/main.cpp
${SOURCE_DIR}/EdgeView.cpp
${SOURCE_DIR}/Controller.cpp
${SOURCE_DIR}/ControllerComm.cpp
${SOURCE_DIR}/ControllerAppMgmt.cpp
)

set(HEADERS
${HEADERS}
${HEADER_DIR}/EdgeView.hpp
${HEADER_DIR}/ApplicationTheme.hpp
${HEADER_DIR}/Controller.hpp
)

if(IOS)
set(RESOURCE_FILE ./resources/ios/EdgeView.qrc)
endif(IOS)

if(MACOS)
set(RESOURCE_FILE ./resources/macos/EdgeView.qrc)
endif(MACOS)

if(WIN32)
set(RESOURCE_FILE ./resources/windows/EdgeView.qrc)
endif(WIN32)

if(ANDROID_LINUX)
set(RESOURCE_FILE ./resources/android/EdgeView.qrc)
endif(ANDROID_LINUX)

if(GNU_LINUX)
set(RESOURCE_FILE ./resources/linux/EdgeView.qrc)
endif(GNU_LINUX)

qt_add_executable(EdgeView ${DLMS_SOURCES} ${DLMS_HEADERS} ${SOURCES} ${HEADERS} ${RESOURCE_FILE})

set_target_properties(EdgeView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER edgeview.sriiixi.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_FRAMEWORK_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/darwin/Info.plist
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/darwin/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

target_link_libraries(EdgeView
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::CorePrivate
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Network
)

install(TARGETS EdgeView
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
