cmake_minimum_required(VERSION 3.26)
project(minecraft)

set(CMAKE_CXX_STANDARD 17)

# Create GLAD as a static library from glad.c
add_library(glad STATIC include/glad.c)
target_include_directories(glad PUBLIC include)

# Find and link GLFW (you must install it or add it yourself)
find_package(glfw3 REQUIRED)

add_executable(minecraft src/main.cpp
        src/minecraft.cpp
        src/minecraft.hpp
        src/timer.cpp
        src/timer.hpp
        src/systems/system.hpp
        src/systems/rendering_system.cpp
        src/systems/rendering_system.hpp)

target_include_directories(minecraft PRIVATE
        include
)

target_link_libraries(minecraft PRIVATE glad glfw)