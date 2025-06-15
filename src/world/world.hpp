//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_WORLD_HPP
#define MINECRAFT_WORLD_HPP

#include "entt/entt.hpp"
#include "chunk.hpp"

class World {
public:
    explicit World(entt::registry &registry);

    void generate();
private:
    entt::registry &registry;

    const int CHUNK_DISTANCE = 5;
};


#endif //MINECRAFT_WORLD_HPP
