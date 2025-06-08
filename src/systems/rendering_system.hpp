//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_RENDERING_SYSTEM_HPP
#define MINECRAFT_RENDERING_SYSTEM_HPP


#include <GLFW/glfw3.h>
#include "system.hpp"

class RenderingSystem : public System {
public:
    RenderingSystem();

    void update(int elapsed) override;

private:
    GLFWwindow *window = nullptr;

    void init_window();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};


#endif //MINECRAFT_RENDERING_SYSTEM_HPP
