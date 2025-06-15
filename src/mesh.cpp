//
// Created by simone on 10/06/25.
//

#include "mesh.hpp"

void Mesh::add_triangle(VertexData vertex_1, VertexData vertex_2, VertexData vertex_3) {
    add_vertex(vertex_1);
    add_vertex(vertex_2);
    add_vertex(vertex_3);
    triangles.push_back({vertex_idx[vertex_1], vertex_idx[vertex_2], vertex_idx[vertex_3]});
}

void Mesh::add_vertex(VertexData vertex) {
    if (!vertex_idx.contains({vertex.position_x, vertex.position_y, vertex.position_z})) {
        int vtx_idx = vertexes.size();
        vertexes.push_back(vertex);
        vertex_idx[vertex] = vtx_idx;
    }
}

std::vector<float> Mesh::get_vertexes() {
    std::vector<float> res;
    for (auto vtx: vertexes) {
        res.push_back(vtx.position_x);
        res.push_back(vtx.position_y);
        res.push_back(vtx.position_z);
        res.push_back(vtx.normal_x);
        res.push_back(vtx.normal_y);
        res.push_back(vtx.normal_z);
        res.push_back(vtx.tex_u);
        res.push_back(vtx.tex_v);

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

