cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME corelib)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Qml Gui)
if(ANDROID)
    
endif()

add_library(${PROJECT_NAME} SHARED

    androidservicemanager.cpp
    currentapplicationhelper.cpp
    applicationpath.cpp
    applicationsettings.cpp
    apppagesmanager.cpp
    colorlistmodel.cpp
    datetimeutility.cpp
    fileutility.cpp
    filewatcher.cpp
    htmlhelper.cpp
    imageutility.cpp
    isoscelestrianglemath.cpp
    itemsvisiblestate.cpp
    jooyaapplication.cpp
    jooyafont.cpp
    jooyalogger.cpp
    jooyanetworkengine.cpp
    jooyaregexp.cpp
    jooyasettings.cpp
    jsonutility.cpp
    materialcolor.cpp
    materialstylehelper.cpp
    message.cpp
    persiandatetime.cpp
    urlutility.cpp
    userlogininfo.cpp
    userloginsettings.cpp
    androidservicemanager.h
    currentapplication.h
    currentapplicationhelper.h
    applicationpath.h
    applicationsettings.h
    apppagesmanager.h
    colorlistmodel.h
    corelib.h
    currentuser.h
    datetimeutility.h
    fileutility.h
    filewatcher.h
    htmlhelper.h
    imageutility.h
    isoscelestrianglemath.h
    itemsvisiblestate.h
    jooyaapplication.h
    jooyafont.h
    jooyalogger.h
    jooyanetworkengine.h
    jooyaregexp.h
    jooyasettings.h
    jsonutility.h
    loginstates.h
    materialcolor.h
    materialcolors.h
    materialshades.h
    materialstyle.h
    materialstylehelper.h
    materialthemes.h
    message.h
    messageboard.h
    operationtypes.h
    persiandatetime.h
    persiandayofweek.h
    qmllive.h
    urlutility.h
    userlogininfo.h
    userloginsettings.h
    userroles.h
    applicationalarmsettings.h
    applicationalarmsettingshelper.h
    applicationalarmsettingshelper.cpp
    alarmclasses.h
    materialstyle.cpp
    apptypesregistrar.h
    apptypesregistrar.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE . ../androidlib/.)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core Qt6::CorePrivate Qt6::Quick Qt6::Qml Qt6::Gui
    androidlib
)

if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_ANDROID_ARCH_ABI}")
endif()
