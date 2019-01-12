cmake_minimum_required(VERSION 3.0.0)
project(new-nav VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(CTest)
enable_testing()

add_subdirectory(framework)
add_subdirectory(app)
add_subdirectory(module)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
