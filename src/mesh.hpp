//
// Created by simone on 10/06/25.
//

#ifndef MINECRAFT_MESH_HPP
#define MINECRAFT_MESH_HPP


#include <vector>
#include <map>
#include "glm/vec3.hpp"

class Mesh {
public:
    void add_vertex(float x, float y, float z);

    void add_triangle(float x_1, float y_1, float z_1,
                      float x_2, float y_2, float z_2,
                      float x_3, float y_3, float z_3);

    void add_vertex(std::array<float, 3> vertex);

    void add_triangle(std::array<float, 3> vertex_1,
                      std::array<float, 3> vertex_2,
                      std::array<float, 3> vertex_3);

    std::vector<float> get_vertexes();

    std::vector<int> get_indexes();

private:
    std::vector<std::array<float, 3>> vertexes;
    std::map<std::array<float, 3>, int> vertex_idx;
    std::vector<std::array<int, 3>> triangles;
};


#endif //MINECRAFT_MESH_HPP
