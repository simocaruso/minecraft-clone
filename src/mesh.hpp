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
    void add_vertex(VertexData vertex);

    void add_triangle(VertexData vertex_1, VertexData vertex_2, VertexData vertex_3);

    std::vector<float> get_vertexes();

    std::vector<int> get_indexes();

private:
    std::vector<VertexData> vertexes;
    std::unordered_map<VertexData, int> vertex_idx;
    std::vector<std::array<int, 3>> triangles;
};


#endif //MINECRAFT_MESH_HPP
