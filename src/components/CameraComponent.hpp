//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_CAMERACOMPONENT_HPP
#define MINECRAFT_CAMERACOMPONENT_HPP

#include "glm/glm.hpp"

struct CameraComponent {
    glm::mat4 view;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    float yaw = -90.0f;
    float pitch = 0.0f;
};

#endif //MINECRAFT_CAMERACOMPONENT_HPP
