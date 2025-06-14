//
// Created by simone on 10/06/25.
//

#include "mesh.hpp"

void Mesh::add_vertex(float x, float y, float z) {
    add_vertex({x, y, z});
}

void Mesh::add_triangle(float x_1, float y_1, float z_1,
                        float x_2, float y_2, float z_2,
                        float x_3, float y_3, float z_3) {
    add_triangle({x_1, y_1, z_1},
                 {x_2, y_2, z_2},
                 {x_3, y_3, z_3});
}

void Mesh::add_vertex(std::array<float, 3> vertex) {
    if (!vertex_idx.contains(vertex)) {
        int vtx_idx = vertexes.size();
        vertexes.push_back(vertex);
        vertex_idx[vertex] = vtx_idx;
    }
}

void Mesh::add_triangle(std::array<float, 3> vertex_1, std::array<float, 3> vertex_2, std::array<float, 3> vertex_3) {
    add_vertex(vertex_1);
    add_vertex(vertex_2);
    add_vertex(vertex_3);
    triangles.push_back({vertex_idx[vertex_1], vertex_idx[vertex_2], vertex_idx[vertex_3]});
}

std::vector<float> Mesh::get_vertexes() {
    std::vector<float> res;
    for (auto vtx: vertexes) {
        for (auto coordinate: vtx) {
            res.push_back(coordinate);
        }
    }
    return res;
}

std::vector<int> Mesh::get_indexes() {
    std::vector<int> res;
    for (auto triangle: triangles) {
        for (auto vtx: triangle) {
            res.push_back(vtx);
        }
    }
    return res;
}
