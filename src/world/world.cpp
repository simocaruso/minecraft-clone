//
// Created by simone on 08/06/25.
//

#include "world.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

World::World(entt::registry &registry) : registry(registry) {
    generate();
}

void World::generate() {
    Chunk chunk;
    auto entity = registry.create();
    auto &transform_component = registry.emplace<TransformComponent>(entity);
    transform_component.position = {0, -10, -20};
    auto &rendering_component = registry.emplace<RenderingComponent>(entity);
    rendering_component.mesh = chunk.get_mesh();
}
