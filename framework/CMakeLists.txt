cmake_minimum_required(VERSION 3.0.0)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(nlohmann_json 3.5.0 REQUIRED PATHS ${NLOHMANN_JSON_ROOT})

set(SRC
    BaseComponent.cpp
    ComponentManager.cpp
    ComponentRegistry.cpp
)

add_library(new-nav-framework ${SRC})

target_include_directories(new-nav-framework PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(new-nav-framework nlohmann_json::nlohmann_json)
target_link_libraries(new-nav-framework Boost::filesystem)
