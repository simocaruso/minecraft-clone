//
// Created by simone on 16/06/25.
//

#ifndef MINECRAFT_CHUNK_MANAGER_HPP
#define MINECRAFT_CHUNK_MANAGER_HPP

#include "entt/entt.hpp"
#include "glm/vec2.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/hash.hpp"
#include "chunk.hpp"

class ChunkManager {
public:
    ChunkManager(int chunk_size, entt::registry &registry);

    void add_chunk(glm::ivec3 position);

    void remove_chunk(glm::ivec2 position);

    bool is_solid(glm::ivec3 position);

private:
    int chunk_size = 0;
    entt::registry &registry;
    std::unordered_map<glm::ivec3, Chunk> chunks;

    void update_neighbor_chunks(glm::ivec3 position);
};


#endif //MINECRAFT_CHUNK_MANAGER_HPP
