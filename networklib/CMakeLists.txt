cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME networklib)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Qml Gui Network WebSockets)
if(ANDROID)
    
endif()

add_library(${PROJECT_NAME} SHARED
    downloadmanager.cpp
    file.cpp
    fileexplorer.cpp
    imagefile.cpp
    imagelistmodel.cpp
    jooyalistitem.cpp
    jooyanetwork.cpp
    jooyanetworkaccessfactory.cpp
    jooyanetworkaccessmanager.cpp
    listmanager.cpp
    networklib.cpp
    newconnectionmodel.cpp
    websockethandler.cpp
    websocketinfo.cpp
    downloadmanager.h
    file.h
    filedownloadstates.h
    fileexplorer.h
    fileuploadstatus.h
    imagefile.h
    imagelistmodel.h
    jooyalistitem.h
    jooyanetwork.h
    jooyanetworkaccessfactory.h
    jooyanetworkaccessmanager.h
    listmanager.h
    networklib.h
    newconnectionmodel.h
    websockethandler.h
    websocketinfo.h
    websocketmanager.h
    websocketstates.h
    downloadservicemanager.h
    downloadservicemanager.cpp
    headercontenttypes.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs/androidlib ${CMAKE_SOURCE_DIR}/libs/corelib)


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core Qt6::CorePrivate Qt6::Quick Qt6::Qml Qt6::Gui Qt6::Network Qt6::WebSockets
    androidlib corelib
)

if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_ANDROID_ARCH_ABI}")
endif()
