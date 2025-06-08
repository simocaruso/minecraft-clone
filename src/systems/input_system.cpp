//
// Created by simone on 08/06/25.
//

#include <GLFW/glfw3.h>
#include "input_system.hpp"
#include "../components/InputComponent.hpp"

float InputSystem::last_mouse_x = 0;
float InputSystem::last_mouse_y = 0;
float InputSystem::x_offset = 0;
float InputSystem::y_offset = 0;


InputSystem::InputSystem(entt::registry &registry) : System(registry) {
    auto inputEntity = registry.create();
    registry.emplace<InputComponent>(inputEntity);
}

void InputSystem::init() {
    glfwSetCursorPos(registry.ctx().get<GLFWwindow*>(), last_mouse_x, last_mouse_y);
    glfwSetCursorPosCallback(registry.ctx().get<GLFWwindow*>(), mouse_callback);
    glfwSetInputMode(registry.ctx().get<GLFWwindow*>(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputSystem::mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in) {
    auto x_pos = static_cast<float>(x_pos_in);
    auto y_pos = static_cast<float>(y_pos_in);

    x_offset = x_pos - last_mouse_x;
    y_offset = last_mouse_y - y_pos;

    last_mouse_x = x_pos;
    last_mouse_y = y_pos;
}

void InputSystem::update(int elapsed) {
    auto view = registry.view<InputComponent>();
    auto inputEntity = *view.begin();
    auto& input = view.get<InputComponent>(inputEntity);
    auto window = registry.ctx().get<GLFWwindow*>();
    input.move_forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    input.move_backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    input.move_left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    input.move_right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    input.move_up = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    input.move_down = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
    input.look_delta_x = x_offset;
    input.look_delta_y = y_offset;
    x_offset = 0;
    y_offset = 0;
}
