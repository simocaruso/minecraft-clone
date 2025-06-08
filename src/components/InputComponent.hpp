//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_INPUTCOMPONENT_HPP
#define MINECRAFT_INPUTCOMPONENT_HPP

struct InputComponent {
    bool move_forward = false;
    bool move_backward = false;
    bool move_left = false;
    bool move_right = false;
    bool move_up = false;
    bool move_down = false;

    float look_delta_x = 0.0f;
    float look_delta_y = 0.0f;
};

#endif //MINECRAFT_INPUTCOMPONENT_HPP
