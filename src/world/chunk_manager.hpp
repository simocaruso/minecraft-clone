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
    ChunkManager(int chunk_size, int chunk_distance, entt::registry &registry);

    void add_chunk(glm::ivec3 position);

    void remove_chunk(glm::ivec3 position);

    bool is_solid(glm::ivec3 position);

    bool exist(glm::ivec3 position);

    void center(glm::ivec3 position);

    void update();

private:
    int chunk_size = 0;
    int chunk_distance;
    entt::registry &registry;
    std::unordered_map<glm::ivec3, Chunk> chunks;

    std::deque<glm::ivec3> to_be_created;

    void update_neighbor_chunks(glm::ivec3 position);

    glm::ivec3 get_chunk_position(glm::ivec3 position) const;

    void process_pending_chunks();

};


#endif //MINECRAFT_CHUNK_MANAGER_HPP
