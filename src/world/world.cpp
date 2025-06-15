//
// Created by simone on 08/06/25.
//

#include "world.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

World::World(entt::registry &registry) : registry(registry) {
}

void World::generate() {
    for (int x = 0; x < CHUNK_DISTANCE; x ++) {
        for (int z = 0; z < CHUNK_DISTANCE; z++) {
            Chunk chunk;
            auto entity = registry.create();
            auto &transform_component = registry.emplace<TransformComponent>(entity);
            transform_component.position = {x * 16, -10, -20 + z * 16};
            auto &rendering_component = registry.emplace<RenderingComponent>(entity);
            rendering_component.mesh = chunk.get_mesh();
        }
    }
}
