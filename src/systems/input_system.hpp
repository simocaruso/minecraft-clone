//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_INPUT_SYSTEM_HPP
#define MINECRAFT_INPUT_SYSTEM_HPP


#include "system.hpp"

class InputSystem : public System {
    void init() override;

public:
    static float last_mouse_x;
    static float last_mouse_y;
    static float x_offset;
    static float y_offset;

    explicit InputSystem(entt::registry &registry);

    void update(int elapsed) override;

    static void mouse_callback(GLFWwindow *window, double x_pos_in, double y_pos_in);
};


#endif //MINECRAFT_INPUT_SYSTEM_HPP
