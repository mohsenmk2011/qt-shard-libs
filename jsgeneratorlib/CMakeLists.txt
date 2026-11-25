cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME jsgeneratorlib)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)

endif()

add_library(${PROJECT_NAME} SHARED
    documentelement.cpp
    javascriptdocument.cpp
    javascriptgenerator.cpp
    javascriptgeneratorlib.cpp
    documentelement.h
    javascriptdocument.h
    javascriptgenerator.h
    javascriptgeneratorlib.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
)
if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_ANDROID_ARCH_ABI}")
endif()
