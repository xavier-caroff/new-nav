cmake_minimum_required(VERSION 3.0.0)
project(new-nav VERSION 0.1.0)

include(CTest)
enable_testing()

set(SRC
    App.cpp
    main.cpp)

add_executable(new-nav ${SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
