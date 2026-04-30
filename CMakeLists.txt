cmake_minimum_required(VERSION 3.16)
project(redis_clone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(redis_clone
    src/main.cpp
    src/server.cpp
    src/parser.cpp
    src/database.cpp
)