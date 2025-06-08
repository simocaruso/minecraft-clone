//
// Created by simone on 08/06/25.
//

#include "camera_system.hpp"
#include "../components/InputComponent.hpp"
#include "../components/CameraComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

CameraSystem::CameraSystem(entt::registry &registry) : System(registry) {
    auto camera = registry.create();
    registry.emplace<CameraComponent>(camera);
}

void CameraSystem::update(int elapsed) {
    process_input(elapsed);
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));

    auto camera = *registry.view<CameraComponent>().begin();
    auto &view = registry.get<CameraComponent>(camera).view;
    view = glm::lookAt(position, position + front, up);
}

void CameraSystem::process_input(int elapsed) {
    auto input = registry.get<InputComponent>(*registry.view<InputComponent>().begin());
    if (input.move_forward) {
        position += front * (elapsed * movement_speed);
    }
    if (input.move_backward) {
        position -= front * (elapsed * movement_speed);
    }
    if (input.move_left) {
        position -= right * (elapsed * movement_speed);
    }
    if (input.move_right) {
        position += right * (elapsed * movement_speed);
    }
    if (input.move_up) {
        position.y += elapsed * movement_speed;
    }
    if (input.move_down) {
        position.y -= elapsed * movement_speed;
    }

    yaw   += input.look_delta_x * mouse_sensitivity;
    pitch += input.look_delta_y * mouse_sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}