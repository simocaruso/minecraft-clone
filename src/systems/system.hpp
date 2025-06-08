//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_SYSTEM_HPP
#define MINECRAFT_SYSTEM_HPP

#define WIDTH 800
#define HEIGHT 600

#include "entt/entt.hpp"

enum SystemType {
    INPUT,
    CAMERA,
    RENDERING,
};

class System {
public:
    explicit System(entt::registry &registry) : registry(registry) {};

    virtual void init() {};

    virtual void update(int elapsed) = 0;

protected:
    entt::registry &registry;
};


#endif //MINECRAFT_SYSTEM_HPP
