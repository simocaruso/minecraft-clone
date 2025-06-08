//
// Created by simone on 08/06/25.
//

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "rendering_system.hpp"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

RenderingSystem::RenderingSystem() {
    init_window();
}

void RenderingSystem::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void RenderingSystem::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void RenderingSystem::update(int elapsed) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
