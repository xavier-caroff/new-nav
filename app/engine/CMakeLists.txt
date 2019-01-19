cmake_minimum_required(VERSION 3.0.0)

find_package(Boost REQUIRED COMPONENTS filesystem program_options system)
find_package(nlohmann_json 3.5.0 REQUIRED PATHS ${NLOHMANN_JSON_ROOT})

set(SRC
    main.cpp
    App.cpp)

add_executable(new-nav-engine ${SRC})

target_link_libraries(new-nav-engine Boost::filesystem Boost::program_options Boost::system)
target_link_libraries(new-nav-engine new-nav-framework)
target_link_libraries(new-nav-engine nlohmann_json::nlohmann_json)

if (UNIX)
    target_link_libraries(new-nav-engine dl)
endif (UNIX)
