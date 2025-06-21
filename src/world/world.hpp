//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_WORLD_HPP
#define MINECRAFT_WORLD_HPP

#include "entt/entt.hpp"
#include "chunk.hpp"
#include "chunk_manager.hpp"

class World {
public:
    explicit World(entt::registry &registry);

    void generate();

    void update();

private:
    const int CHUNK_SIZE = 16;
    const int CHUNK_DISTANCE = 8;
    entt::registry &registry;
    ChunkManager chunk_manager;
};


#endif //MINECRAFT_WORLD_HPP
