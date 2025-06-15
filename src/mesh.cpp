//
// Created by simone on 10/06/25.
//

#include "glad/glad.h"
#include <iostream>
#include "mesh.hpp"

void Mesh::add_triangle(VertexData vertex_1, VertexData vertex_2, VertexData vertex_3) {
    add_vertex(vertex_1);
    add_vertex(vertex_2);
    add_vertex(vertex_3);
    triangles.push_back({vertex_idx[vertex_1], vertex_idx[vertex_2], vertex_idx[vertex_3]});
}

void Mesh::add_vertex(VertexData vertex) {
    if (!vertex_idx.contains(vertex)) {
        vertexes.push_back(vertex);
        vertex_idx[vertex] = vertexes.size() - 1;
    }
}

std::vector<float> Mesh::get_vertexes() {
    if (cache_gpu_shaped_vertexes.empty()) {
        for (auto vtx: vertexes) {
            cache_gpu_shaped_vertexes.push_back(vtx.position_x);
            cache_gpu_shaped_vertexes.push_back(vtx.position_y);
            cache_gpu_shaped_vertexes.push_back(vtx.position_z);
            cache_gpu_shaped_vertexes.push_back(vtx.normal_x);
            cache_gpu_shaped_vertexes.push_back(vtx.normal_y);
            cache_gpu_shaped_vertexes.push_back(vtx.normal_z);
            cache_gpu_shaped_vertexes.push_back(vtx.tex_u);
            cache_gpu_shaped_vertexes.push_back(vtx.tex_v);
        }
    }
    return cache_gpu_shaped_vertexes;
}

std::vector<int> Mesh::get_indexes() {
    if (cache_gpu_shaped_indexes.empty()) {
        for (auto triangle: triangles) {
            for (auto vtx: triangle) {
                cache_gpu_shaped_indexes.push_back(vtx);
            }
        }
    }
    return cache_gpu_shaped_indexes;
}

void Mesh::clear() {
    vertexes.clear();
    vertex_idx.clear();
    triangles.clear();
    cache_gpu_shaped_vertexes.clear();
    cache_gpu_shaped_indexes.clear();
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);

    }
}

unsigned int Mesh::get_VAO() const {
    if (!VAO) {
        std::cout << "Requested VAO not initialized" << std::endl;
    }
    return VAO;
}

void Mesh::create() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, get_vertexes().size() * sizeof(float), get_vertexes().data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_indexes().size() * sizeof(int), get_indexes().data(),
                 GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

int Mesh::get_size() {
    return get_indexes().size();
}


