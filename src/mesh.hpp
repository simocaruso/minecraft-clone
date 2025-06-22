//
// Created by simone on 10/06/25.
//

#ifndef MINECRAFT_MESH_HPP
#define MINECRAFT_MESH_HPP


#include <vector>
#include <unordered_map>
#include "glm/vec3.hpp"
#include "block.hpp"


class Mesh {
public:
    void create();

    bool is_created();

    void add_face(CUBE_FACE_IDX face, glm::ivec3 position);

    void clear_cache();

    unsigned int get_VAO() const;

    int get_size();

private:
    unsigned int VBO, VAO, EBO;
    std::vector<VertexData> vertexes;
    std::unordered_map<VertexData, int> vertex_idx;
    std::vector<std::array<int, 3>> triangles;
    std::vector<float> cache_gpu_shaped_vertexes;
    std::vector<int> cache_gpu_shaped_indexes;
    bool m_is_created = false;

    void add_vertex(VertexData vertex);

    void add_triangle(VertexData vertex_1, VertexData vertex_2, VertexData vertex_3);

    std::vector<int> get_indexes();

    std::vector<float> get_vertexes();

};


#endif //MINECRAFT_MESH_HPP
