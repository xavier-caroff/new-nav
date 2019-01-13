cmake_minimum_required(VERSION 3.0.0)

set(SRC
    ComponentRegistry.cpp
    BaseComponent.cpp)

add_library(new-nav-framework ${SRC})

target_include_directories(new-nav-framework PUBLIC ${CMAKE_CURRENT_LIST_DIR})