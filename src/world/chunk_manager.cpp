//
// Created by simone on 16/06/25.
//

#include <iostream>
#include "chunk_manager.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

ChunkManager::ChunkManager(int chunk_size, entt::registry &registry) : chunk_size(chunk_size), registry(registry) {
}

void ChunkManager::add_chunk(glm::ivec3 position) {
    Chunk chunk{chunk_size, position, registry};
    chunks.emplace(position, chunk);
    update_neighbor_chunks(position);
}

void ChunkManager::update_neighbor_chunks(glm::ivec3 position) {
    position = get_chunk_position(position);
    auto directions = {glm::ivec3(-1, 0, 0),
                       glm::ivec3(1, 0, 0),
                       glm::ivec3(0, 0, -1),
                       glm::ivec3(0, 0, 1)};
    for (auto direction: directions) {
        auto neighbor_chunk = position + (direction * chunk_size);
        if (chunks.contains(neighbor_chunk))
            chunks.at(neighbor_chunk).invalidate_mesh();
    }
}

void ChunkManager::remove_chunk(glm::ivec3 position) {
    if (chunks.contains(position)) {
        chunks.at(position).destroy();
        chunks.erase(position);
        update_neighbor_chunks(position);
    }
}

glm::ivec3 ChunkManager::get_chunk_position(glm::ivec3 position) const {
    return glm::ivec3(std::floor((float) position.x / (float) chunk_size), 0,
                      std::floor((float) position.z / (float) chunk_size)) *
           chunk_size;
}

bool ChunkManager::is_solid(glm::ivec3 position) {
    glm::ivec3 chunk_position = get_chunk_position(position);
    if (!chunks.contains(chunk_position)) {
        return false;
    }
    auto &chunk = chunks.at(chunk_position);
    return chunk.is_solid({(position.x % chunk_size + chunk_size) % chunk_size, position.y,
                           (position.z % chunk_size + chunk_size) % chunk_size});
}

void ChunkManager::center(glm::ivec3 position, int max_distance) {
    glm::ivec3 center = get_chunk_position(position);
    auto distance = max_distance * chunk_size;
    if (chunks.contains({center.x - distance, center.y, center.z})) {
        for (int z = -distance; z <= distance; z += chunk_size) {
            remove_chunk({center.x - distance, center.y, center.z + z});
        }
    }
    if (chunks.contains({center.x + distance, center.y, center.z})) {
        for (int z = -distance; z <= distance; z += chunk_size) {
            remove_chunk({center.x + distance, center.y, center.z + z});
        }
    }
    if (chunks.contains({center.x, center.y, center.z - distance})) {
        for (int x = -distance; x <= distance; x += chunk_size) {
            remove_chunk({center.x + x, center.y, center.z - distance});
        }
    }
    if (chunks.contains({center.x, center.y, center.z + distance})) {
        for (int x = -distance; x <= distance; x += chunk_size) {
            remove_chunk({center.x + x, center.y, center.z + distance});
        }
    }

    for (auto &[chunk_pos , chunk]: chunks) {
        chunk.update_mesh(*this);
    }

}

