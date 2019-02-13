cmake_minimum_required(VERSION 3.0.0)

find_package(Boost REQUIRED)

set(SRC
    module.cpp
    DataBufferDisplay.cpp
    SerialReader.cpp
    TcpServer.cpp)

add_library(new-nav-module-io SHARED ${SRC})

target_link_libraries(new-nav-module-io new-nav-framework)
