//
// Created by simone on 07/06/25.
//

#ifndef MINECRAFT_MINECRAFT_HPP
#define MINECRAFT_MINECRAFT_HPP

#include <memory>
#include <vector>
#include <map>
#include "systems/system.hpp"
#include "entt/entt.hpp"
#include "world.hpp"

class Minecraft {
public:
    void start();

private:
    std::map<SystemType, std::unique_ptr<System>> systems;
    entt::registry registry;
    World world = World(registry);

    void run_game_loop();

    void init_systems();
};


#endif //MINECRAFT_MINECRAFT_HPP
