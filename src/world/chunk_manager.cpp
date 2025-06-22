//
// Created by simone on 16/06/25.
//

#include "chunk_manager.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/CameraComponent.hpp"

ChunkManager::ChunkManager(int chunk_size, int chunk_distance, entt::registry &registry) :
        chunk_size(chunk_size), chunk_distance(chunk_distance), registry(registry) {
}

void ChunkManager::add_chunk(glm::ivec3 position) {
    chunks.emplace(position, Chunk(chunk_size, position, registry));
    to_be_created.push_back(position);
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
            chunks.at(neighbor_chunk).update_mesh(*this);
    }
}

void ChunkManager::remove_chunk(glm::ivec3 position) {
    if (chunks.contains(position)) {
        chunks.at(position).destroy();
        chunks.erase(position);
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
        return true;
    }
    auto &chunk = chunks.at(chunk_position);
    return chunk.is_solid({(position.x % chunk_size + chunk_size) % chunk_size, position.y,
                           (position.z % chunk_size + chunk_size) % chunk_size});
}

bool ChunkManager::exist(glm::ivec3 position) {
    return chunks.contains(get_chunk_position(position));
}

void ChunkManager::center(glm::ivec3 position) {
    glm::ivec3 center = get_chunk_position(position);
    auto distance = chunk_distance * chunk_size;
    auto to_remove = (chunk_distance + 1) * chunk_size;
    if (chunks.contains({center.x - to_remove, center.y, center.z})) {
        for (int z = -to_remove; z <= to_remove; z += chunk_size) {
            remove_chunk({center.x - to_remove, center.y, center.z + z});
        }
    }
    if (!chunks.contains({center.x - distance, center.y, center.z})) {
        for (int z = -distance; z <= distance; z += chunk_size) {
            add_chunk({center.x - distance, center.y, center.z + z});
        }
    }
    if (chunks.contains({center.x + to_remove, center.y, center.z})) {
        for (int z = -to_remove; z <= to_remove; z += chunk_size) {
            remove_chunk({center.x + to_remove, center.y, center.z + z});
        }
    }
    if (!chunks.contains({center.x + distance, center.y, center.z})) {
        for (int z = -distance; z <= distance; z += chunk_size) {
            add_chunk({center.x + distance, center.y, center.z + z});
        }
    }
    if (chunks.contains({center.x, center.y, center.z - to_remove})) {
        for (int x = -to_remove; x <= to_remove; x += chunk_size) {
            remove_chunk({center.x + x, center.y, center.z - to_remove});
        }
    }
    if (!chunks.contains({center.x, center.y, center.z - distance})) {
        for (int x = -distance; x <= distance; x += chunk_size) {
            add_chunk({center.x + x, center.y, center.z - distance});
        }
    }
    if (chunks.contains({center.x, center.y, center.z + to_remove})) {
        for (int x = -to_remove; x <= to_remove; x += chunk_size) {
            remove_chunk({center.x + x, center.y, center.z + to_remove});
        }
    }
    if (!chunks.contains({center.x, center.y, center.z + distance})) {
        for (int x = -distance; x <= distance; x += chunk_size) {
            add_chunk({center.x + x, center.y, center.z + distance});
        }
    }
}

void ChunkManager::process_pending_chunks() {
    if (!to_be_created.empty()) {
        auto to_create = to_be_created.front();
        to_be_created.pop_front();
        while (!to_be_created.empty() && !chunks.contains(to_create)) {
            to_create = to_be_created.front();
            to_be_created.pop_front();
        }
        if (chunks.contains(to_create)) {
            chunks.at(to_create).update_mesh(*this);
            update_neighbor_chunks(to_create);
        }
    }
}

void ChunkManager::update() {
    auto player_position = registry.get<CameraComponent>(*registry.view<CameraComponent>().begin()).position;
    center(player_position);

    process_pending_chunks();
}
