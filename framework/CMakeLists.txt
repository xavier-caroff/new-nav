cmake_minimum_required(VERSION 3.0.0)

set(SRC
    BaseComponent.cpp
    ComponentManager.cpp
    ComponentRegistry.cpp
)

add_library(new-nav-framework ${SRC})

target_include_directories(new-nav-framework PUBLIC ${CMAKE_CURRENT_LIST_DIR})