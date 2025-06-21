//
// Created by simone on 08/06/25.
//

#include "world.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"
#include "../components/CameraComponent.hpp"

World::World(entt::registry &registry) : registry(registry), chunk_manager({CHUNK_SIZE, registry}) {
}

void World::generate() {
    for (int x = -CHUNK_DISTANCE; x < CHUNK_DISTANCE+1; x++) {
        for (int z = -CHUNK_DISTANCE; z < CHUNK_DISTANCE+1; z++) {
            chunk_manager.add_chunk({x * CHUNK_SIZE, 0, z * CHUNK_SIZE});
        }
    }
}

void World::update() {
    auto player_position = registry.get<CameraComponent>(*registry.view<CameraComponent>().begin()).position;
    chunk_manager.center(player_position, CHUNK_DISTANCE);
}
