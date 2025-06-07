cmake_minimum_required(VERSION 3.26)
project(minecraft)

set(CMAKE_CXX_STANDARD 17)

add_executable(minecraft src/main.cpp
        src/minecraft.cpp
        src/minecraft.hpp
        src/timer.cpp
        src/timer.hpp)
