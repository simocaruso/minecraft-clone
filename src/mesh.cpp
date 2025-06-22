//
// Created by simone on 10/06/25.
//

#include "glad/glad.h"
#include <iostream>
#include "mesh.hpp"

void Mesh::add_face(CUBE_FACE_IDX face, glm::ivec3 position) {
    auto start_idx = face * VERTEX_DATA_SIZE * 6;
    for (int i = start_idx; i < start_idx + VERTEX_DATA_SIZE * 6; i += VERTEX_DATA_SIZE * 3) {
        add_triangle({VertexData{CUBE_VERTICES[i] + position.x,
                                      CUBE_VERTICES[i + 1] + position.y,
                                      CUBE_VERTICES[i + 2] + position.z,
                                      CUBE_VERTICES[i + 3],
                                      CUBE_VERTICES[i + 4],
                                      CUBE_VERTICES[i + 5],
                                      CUBE_VERTICES[i + 6],
                                      CUBE_VERTICES[i + 7]}
                          },
                          {VertexData{CUBE_VERTICES[i + 8] + position.x,
                                      CUBE_VERTICES[i + 9] + position.y,
                                      CUBE_VERTICES[i + 10] + position.z,
                                      CUBE_VERTICES[i + 11],
                                      CUBE_VERTICES[i + 12],
                                      CUBE_VERTICES[i + 13],
                                      CUBE_VERTICES[i + 14],
                                      CUBE_VERTICES[i + 15]}
                          },
                          {VertexData{CUBE_VERTICES[i + 16] + position.x,
                                      CUBE_VERTICES[i + 17] + position.y,
                                      CUBE_VERTICES[i + 18] + position.z,
                                      CUBE_VERTICES[i + 19],
                                      CUBE_VERTICES[i + 20],
                                      CUBE_VERTICES[i + 21],
                                      CUBE_VERTICES[i + 22],
                                      CUBE_VERTICES[i + 23]}
                          }
        );
    }
}

bool Mesh::is_created() {
    return m_is_created;
}

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

void Mesh::clear_cache() {
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

    m_is_created = false;
}

unsigned int Mesh::get_VAO() const {
    if (!VAO) {
        std::cout << "Requested VAO not initialized" << std::endl;
    }
    return VAO;
}

void Mesh::create() {
    clear_cache();

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

    m_is_created = true;
}

int Mesh::get_size() {
    return get_indexes().size();
}


