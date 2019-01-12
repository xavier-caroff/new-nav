cmake_minimum_required(VERSION 3.0.0)

find_package(Boost REQUIRED COMPONENTS filesystem system)

set(SRC
    main.cpp
    App.cpp)

add_executable(new-nav-engine ${SRC})

target_link_libraries(new-nav-engine Boost::filesystem Boost::system)