cmake_minimum_required(VERSION 3.0.0)

find_package(Boost REQUIRED)

set(SRC
    module.cpp
    TcpServer.cpp)

add_library(new-nav-module-io SHARED ${SRC})
