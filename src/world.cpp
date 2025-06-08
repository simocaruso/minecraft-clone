//
// Created by simone on 08/06/25.
//

#include "world.hpp"
#include "components/TransformComponent.hpp"

World::World(entt::registry &registry) : registry(registry) {
    create();
}

void World::create() {
    for (int x = -5; x < 5; x++) {
        for (int z = -10; z < -5; z++) {
            auto entity = registry.create();
            auto &transform_component = registry.emplace<TransformComponent>(entity);
            transform_component.position = {x, -3.0f, z};
        }
    }
}
