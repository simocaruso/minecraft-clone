//
// Created by simone on 08/06/25.
//

#include <GLFW/glfw3.h>
#include "input_system.hpp"
#include "../components/InputComponent.hpp"

float InputSystem::x_offset = 0;
float InputSystem::y_offset = 0;


InputSystem::InputSystem(entt::registry &registry) : System(registry) {
    auto inputEntity = registry.create();
    registry.emplace<InputComponent>(inputEntity);
}

void InputSystem::init() {
    glfwSetCursorPos(registry.ctx().get<GLFWwindow *>(), WIDTH / 2, HEIGHT / 2);
    glfwSetCursorPosCallback(registry.ctx().get<GLFWwindow *>(), mouse_callback);
    glfwSetInputMode(registry.ctx().get<GLFWwindow *>(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void InputSystem::mouse_callback(GLFWwindow *window, double x_pos_in, double y_pos_in) {
    auto x_pos = static_cast<float>(x_pos_in);
    auto y_pos = static_cast<float>(y_pos_in);

    x_offset = x_pos - WIDTH / 2;
    y_offset = HEIGHT / 2 - y_pos;

    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
}

void InputSystem::update(int elapsed) {
    auto view = registry.view<InputComponent>();
    auto inputEntity = *view.begin();
    auto &input = view.get<InputComponent>(inputEntity);
    auto window = registry.ctx().get<GLFWwindow *>();
    input.move_forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    input.move_backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    input.move_left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    input.move_right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    input.move_up = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    input.move_down = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
    input.look_delta_x = x_offset;
    input.look_delta_y = y_offset;

    input.toggle_input_render = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
    x_offset = 0;
    y_offset = 0;
}
