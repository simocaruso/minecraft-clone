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
    chunk.update_mesh(*this);
    update_neighbor_chunks(position);
}

void ChunkManager::update_neighbor_chunks(glm::ivec3 position) {
    if (chunks.contains({position.x - chunk_size, position.y, position.z}))
        chunks.at({position.x - chunk_size, position.y, position.z}).update_mesh(*this);
    if (chunks.contains({position.x + chunk_size, position.y, position.z}))
        chunks.at({position.x + chunk_size, position.y, position.z}).update_mesh(*this);
    if (chunks.contains({position.x, position.y, position.z - chunk_size}))
        chunks.at({position.x, position.y, position.z - chunk_size}).update_mesh(*this);
    if (chunks.contains({position.x, position.y, position.z + chunk_size}))
        chunks.at({position.x, position.y, position.z + chunk_size}).update_mesh(*this);
}

void ChunkManager::remove_chunk(glm::ivec2 position) {

}

bool ChunkManager::is_solid(glm::ivec3 position) {
    glm::ivec3 chunk_position =
            glm::ivec3(std::floor(position.x / (float) chunk_size), 0, std::floor(position.z / (float) chunk_size)) *
            chunk_size;
    if (!chunks.contains(chunk_position)) {
        return false;
    }
    auto &chunk = chunks.at(chunk_position);
    return chunk.is_solid({position.x % chunk_size, position.y, position.z % chunk_size});;
}

