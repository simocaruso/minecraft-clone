//
// Created by simone on 10/06/25.
//

#include <iostream>
#include "chunk.hpp"
#include "chunk_manager.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

Chunk::Chunk(int size, glm::ivec3 in_world_position, entt::registry &registry) : size(size),
                                                                                 in_world_position(in_world_position),
                                                                                 registry(registry) {
    generate();
    entity = registry.create();
    auto &transform_component = registry.emplace<TransformComponent>(entity);
    auto &rendering_component = registry.emplace<RenderingComponent>(entity);
    transform_component.position = in_world_position;
}


void Chunk::generate() {
    srandom(time(nullptr));
    for (int x = 0; x < size; x++) {
        for (int z = 0; z < size; z++) {
            height_map[std::make_pair(x, z)] = random() % MAX_HEIGHT;
        }
    }
}

void Chunk::initialize_column(ChunkManager &chunk_manager, Mesh &mesh, const CUBE_FACE_IDX &face,
                              const glm::ivec3 &position) {
    glm::ivec3 off_set;
    switch (face) {
        case TOP:
            off_set = {0, 1, 0};
            break;
        case BOTTOM:
            off_set = {0, -1, 0};
            break;
        case LEFT:
            off_set = {-1, 0, 0};
            break;
        case RIGHT:
            off_set = {1, 0, 0};
            break;
        case BACK:
            off_set = {0, 0, -1};
            break;
        case FRONT:
            off_set = {0, 0, 1};
            break;
    }
    auto height = height_map[std::make_pair(position.x, position.z)];
    for (int y = height; y >= MIN_HEIGHT; y--) {
        if ((!chunk_manager.is_solid(glm::ivec3(in_world_position.x + position.x,
                                                in_world_position.y + position.y + y,
                                                in_world_position.z + position.z) + off_set))) {
            mesh.add_face(face, {position.x, y, position.z});
        } else {
            break;
        }
    }
}

void Chunk::initialize_mesh(ChunkManager &chunk_manager) {
    auto &mesh = registry.get<RenderingComponent>(entity).mesh;
    for (auto &[coords, height]: height_map) {
        auto x = coords.first;
        auto z = coords.second;
        auto y = in_world_position.y;
        initialize_column(chunk_manager, mesh, TOP, {x, y, z});
        initialize_column(chunk_manager, mesh, BOTTOM, {x, y, z});
        initialize_column(chunk_manager, mesh, RIGHT, {x, y, z});
        initialize_column(chunk_manager, mesh, LEFT, {x, y, z});
        initialize_column(chunk_manager, mesh, FRONT, {x, y, z});
        initialize_column(chunk_manager, mesh, BACK, {x, y, z});
    }
    mesh.create();
    if (!chunk_manager.exist(in_world_position + glm::ivec3(size, 0, 0))) {
        pending[RIGHT] = true;
    }
    if (!chunk_manager.exist(in_world_position + glm::ivec3(-size, 0, 0))) {
        pending[LEFT] = true;
    }
    if (!chunk_manager.exist(in_world_position + glm::ivec3(0, 0, size))) {
        pending[FRONT] = true;
    }
    if (!chunk_manager.exist(in_world_position + glm::ivec3(0, 0, -size))) {
        pending[BACK] = true;
    }
}


void Chunk::update_mesh(ChunkManager &chunk_manager) {
    auto &rendering_component = registry.get<RenderingComponent>(entity);
    auto &mesh = rendering_component.mesh;
    if (mesh.is_created()) {
        if (pending[RIGHT] && chunk_manager.exist(in_world_position + glm::ivec3(size, 0, 0))) {
            for (int z = 0; z < size; z++) {
                initialize_column(chunk_manager, mesh, RIGHT, {size-1, 0, z});
            }
            pending[RIGHT] = false;
            mesh.create();
        }
        if (pending[LEFT] && chunk_manager.exist(in_world_position + glm::ivec3(-size, 0, 0))) {
            for (int z = 0; z < size; z++) {
                initialize_column(chunk_manager, mesh, LEFT, {0, 0, z});
            }
            pending[LEFT] = false;
            mesh.create();
        }
        if (pending[FRONT] && chunk_manager.exist(in_world_position + glm::ivec3(0, 0, size))) {
            for (int x = 0; x < size; x++) {
                initialize_column(chunk_manager, mesh, FRONT, {x, 0, size-1});
            }
            pending[FRONT] = false;
            mesh.create();
        }
        if (pending[BACK] && chunk_manager.exist(in_world_position + glm::ivec3(0, 0, -size))) {
            for (int x = 0; x < size; x++) {
                initialize_column(chunk_manager, mesh, BACK, {x, 0, 0});
            }
            pending[BACK] = false;
            mesh.create();
        }
        return;
    } else {
        initialize_mesh(chunk_manager);
    }


}

bool Chunk::is_solid(glm::ivec3 position) {
    if (position.y < MIN_HEIGHT)
        return false;
    return position.y < height_map[std::make_pair(position.x, position.z)];
}

void Chunk::destroy() {
    registry.destroy(entity);
}


