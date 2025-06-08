//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_SYSTEM_HPP
#define MINECRAFT_SYSTEM_HPP

#include "entt/entt.hpp"

enum SystemType {
    RENDERING,
};

class System {
public:
    explicit System(entt::registry &registry): registry(registry) {};

    virtual void update(int elapsed) = 0;

protected:
    entt::registry &registry;
};




#endif //MINECRAFT_SYSTEM_HPP
