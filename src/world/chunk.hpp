//
// Created by simone on 10/06/25.
//

#ifndef MINECRAFT_CHUNK_HPP
#define MINECRAFT_CHUNK_HPP


#include <map>
#include <bitset>
#include "../mesh.hpp"
#include "glm/vec2.hpp"
#include "entt/entt.hpp"

class ChunkManager;

class Chunk {
public:
    Chunk(int size, glm::ivec3 in_world_position, entt::registry &registry);

    ~Chunk() = default;

    void destroy();

    void update_mesh(ChunkManager &chunk_manager);

    bool is_solid(glm::ivec3 position);

private:
    int size = 0;
    static const int MAX_HEIGHT = 10;
    static const int MIN_HEIGHT = 0;
    std::map<std::pair<int, int>, int> height_map;
    std::bitset<4> pending;
    glm::ivec3 in_world_position;
    entt::registry &registry;
    entt::entity entity;

    void generate();

    void initialize_mesh(ChunkManager &chunk_manager);

    void initialize_column(ChunkManager &chunk_manager, Mesh &mesh,
                           const CUBE_FACE_IDX &face, const glm::ivec3 &position);
};


#endif //MINECRAFT_CHUNK_HPP
