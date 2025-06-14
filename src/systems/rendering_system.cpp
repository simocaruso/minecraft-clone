//
// Created by simone on 08/06/25.
//

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "rendering_system.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/RederingComponent.hpp"
#include "../components/InputComponent.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RenderingSystem::RenderingSystem(entt::registry &registry) : System(registry) {
    init_window();
    shader.init();
}

void RenderingSystem::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to generate GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    registry.ctx().emplace<GLFWwindow *>(window);
    glEnable(GL_DEPTH_TEST);
}

void RenderingSystem::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void RenderingSystem::toggle_render_mode() {
    int TOGGLED_RENDER_MODE_TIME = 500;
    if (toggled_render_mode.elapsed() > TOGGLED_RENDER_MODE_TIME &&
        registry.get<InputComponent>(*registry.view<InputComponent>().begin()).toggle_input_render) {
        toggled_render_mode.reset();
        GLint mode;
        glGetIntegerv(GL_POLYGON_MODE, &mode);
        if (mode == GL_FILL) {
            mode = GL_LINE;
        } else {
            mode = GL_FILL;
        }
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}

void RenderingSystem::update(int elapsed) {
    toggle_render_mode();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    auto projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
    auto &view = registry.get<CameraComponent>(*registry.view<CameraComponent>().begin()).view;
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    for (auto cube: registry.view<TransformComponent>()) {
        auto &mesh = registry.get<RenderingComponent>(cube).mesh;
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh.get_vertexes().size() * sizeof(float), mesh.get_vertexes().data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.get_indexes().size() * sizeof(int), mesh.get_indexes().data(),
                     GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO);
        auto model = glm::translate(glm::mat4(1.0f), registry.get<TransformComponent>(cube).position);
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, mesh.get_indexes().size(), GL_UNSIGNED_INT, 0);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }


    glfwSwapBuffers(registry.ctx().get<GLFWwindow *>());
    glfwPollEvents();
}
