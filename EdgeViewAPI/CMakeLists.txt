cmake_minimum_required(VERSION 3.16)

set(Project EdgeViewAPI)

project(${Project} VERSION 3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_SUFFIX "")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(UNIX AND NOT APPLE)
        message("-- Configuring for Linux ...")
        set(GNU_LINUX TRUE)
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

find_package(Qt6 6 REQUIRED COMPONENTS Core Network Sql)
qt_standard_project_setup(REQUIRES 6)

set(CORE_SOURCE_DIR ./core/src)
set(CORE_HEADER_DIR ./core/include)
set(HTTP_SOURCE_DIR ./http/src)
set(HTTP_HEADER_DIR ./http/include)
set(DATAACCESS_SOURCE_DIR ./dataaccess/src)
set(DATAACCESS_HEADER_DIR ./dataaccess/include)
set(MODEL_SOURCE_DIR ./model/src)
set(MODEL_HEADER_DIR ./model/include)

include_directories(${PROJECT_HEADER_DIR} ./include ./core/include ./http/include ./dataaccess/include ./model/include)

set(CORE_SOURCES
${CORE_SOURCES}
${CORE_SOURCE_DIR}/main.cpp
${CORE_SOURCE_DIR}/EdgeViewAPIServer.cpp
${CORE_SOURCE_DIR}/RequestProcessor.cpp
)

set(CORE_HEADERS
${CORE_HEADERS}
${CORE_HEADER_DIR}/EdgeViewAPIServer.hpp
${CORE_HEADER_DIR}/RequestProcessor.hpp
)

set(HTTP_SOURCES
${HTTP_SOURCES}
${HTTP_SOURCE_DIR}/QtHttpClientWrapper.cpp
${HTTP_SOURCE_DIR}/QtHttpHeader.cpp
${HTTP_SOURCE_DIR}/QtHttpReply.cpp
${HTTP_SOURCE_DIR}/QtHttpRequest.cpp
${HTTP_SOURCE_DIR}/QtHttpServer.cpp
)

set(HTTP_HEADERS
${HTTP_HEADERS}
${HTTP_HEADER_DIR}/QtHttpClientWrapper.hpp
${HTTP_HEADER_DIR}/QtHttpHeader.hpp
${HTTP_HEADER_DIR}/QtHttpReply.hpp
${HTTP_HEADER_DIR}/QtHttpRequest.hpp
${HTTP_HEADER_DIR}/QtHttpServer.hpp
)

set(DATAACCESS_SOURCES
${DATAACCESS_SOURCES}
${DATAACCESS_SOURCE_DIR}/DbInit.cpp
${DATAACCESS_SOURCE_DIR}/DataEntity.cpp
${DATAACCESS_SOURCE_DIR}/DataInterface.cpp
)

set(DATAACCESS_HEADERS
${DATAACCESS_HEADERS}
${DATAACCESS_HEADER_DIR}/DbInit.hpp
${DATAACCESS_HEADER_DIR}/DataEntity.hpp
${DATAACCESS_HEADER_DIR}/DataInterface.hpp
)

set(MODEL_SOURCES
${MODEL_SOURCES}
${MODEL_SOURCE_DIR}/Users.cpp
)

set(MODEL_HEADERS
${MODEL_HEADERS}
${MODEL_HEADER_DIR}/Users.hpp
)

qt_add_executable(${Project} ${CORE_SOURCES} ${CORE_HEADERS} ${HTTP_SOURCES} ${HTTP_HEADERS} ${DATAACCESS_SOURCES} ${DATAACCESS_HEADERS} ${MODEL_SOURCES} ${MODEL_HEADERS})

target_link_libraries(${Project}
    PRIVATE Qt6::Core
    PRIVATE Qt6::CorePrivate
    PRIVATE Qt6::Network
    PRIVATE Qt6::Sql
)

install(TARGETS ${Project}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
