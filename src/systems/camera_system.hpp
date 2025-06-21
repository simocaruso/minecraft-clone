//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_CAMERA_SYSTEM_HPP
#define MINECRAFT_CAMERA_SYSTEM_HPP

#include "system.hpp"
#include "glm/glm.hpp"

class CameraSystem : public System {
public:
    explicit CameraSystem(entt::registry &registry);

    void update(int elapsed) override;

private:
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right{};
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    float movement_speed = 0.03f;
    float mouse_sensitivity = 0.2f;

    void process_input(int elapsed);
};


#endif //MINECRAFT_CAMERA_SYSTEM_HPP
