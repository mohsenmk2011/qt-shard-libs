cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME androidlib)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml)

add_library(${PROJECT_NAME} SHARED
    alarminfo.cpp
    alarmmanager.cpp
    androiddeeplinkmanager.cpp

    androidsplashanimator.cpp
    androidutility.cpp

    jooyaandroidcontext.cpp
    mainandroidactivity.cpp
    notificationclient.cpp
    packageinfomanager.cpp
    sharemanager.cpp
    androidpermissionmanager.cpp
    smsmanager.cpp
    alarminfo.h
    alarmmanager.h
    alarmtypes.h
    androiddeeplinkmanager.h

    androidlib.h
    androidsplashanimator.h
    androidutility.h

    jooyaandroidcontext.h
    mainandroidactivity.h
    notificationclient.h
    packageinfomanager.h
    permissiontypes.h
    sharemanager.h
    androidpermissionmanager.h
    smsmanager.h
    intervalunits.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core Qt6::CorePrivate Qt6::Gui Qt6::Qml
)
if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_ANDROID_ARCH_ABI}")
endif()
