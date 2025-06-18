//
// Created by simone on 08/06/25.
//

#include "world.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

World::World(entt::registry &registry) : registry(registry), chunk_manager({CHUNK_SIZE, registry}) {
}

void World::generate() {
    for (int x = 0; x < CHUNK_DISTANCE; x++) {
        for (int z = 0; z < CHUNK_DISTANCE; z++) {
            chunk_manager.add_chunk({x * CHUNK_SIZE, 0, z * CHUNK_SIZE});
        }
    }
}
