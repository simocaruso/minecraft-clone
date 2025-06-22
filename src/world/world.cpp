//
// Created by simone on 08/06/25.
//

#include <iostream>
#include "world.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"
#include "../components/CameraComponent.hpp"

World::World(entt::registry &registry) : registry(registry), chunk_manager({CHUNK_SIZE, CHUNK_DISTANCE, registry}) {
}

void World::generate() {
    for (int x = -CHUNK_DISTANCE; x <= CHUNK_DISTANCE; x++) {
        for (int z = -CHUNK_DISTANCE; z <= CHUNK_DISTANCE; z++) {
            chunk_manager.add_chunk({x * CHUNK_SIZE, 0, z * CHUNK_SIZE});
        }
    }
}

void World::update() {
    chunk_manager.update();
}
