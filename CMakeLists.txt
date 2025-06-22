cmake_minimum_required(VERSION 3.26)
project(minecraft)

set(CMAKE_CXX_STANDARD 20)

# Create GLAD as a static library from glad.c
add_library(glad STATIC include/glad.c
        src/components/TransformComponent.hpp
        src/components/InputComponent.hpp
        src/components/CameraComponent.hpp
        src/components/RederingComponent.hpp
        include/fast_noise_lite/fast_noise_lite.hpp
)
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
        src/systems/rendering_system.hpp
        src/world/world.cpp
        src/world/world.hpp
        src/file_manager.cpp
        src/file_manager.hpp
        src/systems/shader.cpp
        src/systems/shader.hpp
        src/systems/input_system.cpp
        src/systems/input_system.hpp
        src/systems/camera_system.cpp
        src/systems/camera_system.hpp
        src/world/chunk.cpp
        src/world/chunk.hpp
        src/mesh.cpp
        src/mesh.hpp
        src/atlas.cpp
        src/atlas.hpp
        src/block.hpp
        src/world/chunk_manager.cpp
        src/world/chunk_manager.hpp)

add_custom_target(
        CopyShader ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shader ./shader
        COMMENT "Copying shader directory to output"
)

add_dependencies(${PROJECT_NAME} CopyShader)


add_custom_target(
        CopyRes ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ./res
        COMMENT "Copying res directory to output"
)

add_dependencies(${PROJECT_NAME} CopyRes)

target_include_directories(minecraft PRIVATE
        include
)

target_link_libraries(minecraft PRIVATE glad glfw)