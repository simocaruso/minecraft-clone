//
// Created by simone on 07/06/25.
//

#ifndef MINECRAFT_MINECRAFT_HPP
#define MINECRAFT_MINECRAFT_HPP

#include <memory>
#include <vector>
#include <map>
#include "systems/system.hpp"

class Minecraft {
public:
    void start();

private:
    std::map<SystemType, std::unique_ptr<System>> systems;

    void run_game_loop();

    void init_systems();
};


#endif //MINECRAFT_MINECRAFT_HPP
