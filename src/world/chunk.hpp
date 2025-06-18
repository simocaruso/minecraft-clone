//
// Created by simone on 10/06/25.
//

#ifndef MINECRAFT_CHUNK_HPP
#define MINECRAFT_CHUNK_HPP


#include <map>
#include "../mesh.hpp"
#include "glm/vec2.hpp"
#include "entt/entt.hpp"

class ChunkManager;

class Chunk {
public:
    Chunk(int size, glm::ivec3 in_world_position, entt::registry &registry);

    ~Chunk() = default;

    void update_mesh(ChunkManager &chunk_manager);

    bool is_solid(glm::ivec3 position);

private:
    int size = 0;
    static const int MAX_HEIGHT = 5;
    std::map<std::pair<int, int>, int> height_map;
    glm::ivec3 in_world_position;
    entt::registry &registry;
    entt::entity entity;

    void generate();

};


#endif //MINECRAFT_CHUNK_HPP
