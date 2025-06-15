//
// Created by simone on 10/06/25.
//

#include <stdexcept>
#include "chunk.hpp"
#include "../block.hpp"

Chunk::Chunk() {
    generate();
}

void Chunk::generate() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int z = 0; z < SIZE; z++) {
                height_map[std::make_pair(x, z)] = rand() % MAX_HEIGHT + (int) MAX_HEIGHT / 2;
            }
        }
    }

}

Mesh Chunk::get_mesh() {
    if (!dirty) {
        return mesh;
    }
    for (auto cell: height_map) {
        int min_near_y = cell.second;
        if (height_map.contains({cell.first.first - 1, cell.first.second})) {
            min_near_y = std::min(min_near_y, height_map[std::make_pair(cell.first.first - 1, cell.first.second)]);
        }
        if (height_map.contains({cell.first.first + 1, cell.first.second})) {
            min_near_y = std::min(min_near_y, height_map[std::make_pair(cell.first.first + 1, cell.first.second)]);
        }
        if (height_map.contains({cell.first.first, cell.first.second - 1})) {
            min_near_y = std::min(min_near_y, height_map[std::make_pair(cell.first.first, cell.first.second - 1)]);
        }
        if (height_map.contains({cell.first.first, cell.first.second + 1})) {
            min_near_y = std::min(min_near_y, height_map[std::make_pair(cell.first.first, cell.first.second + 1)]);
        }
        for (int y = min_near_y; y < cell.second + 1; y++) {
            for (int i = 0; i < CUBE_INDICES.size(); i += 3) {
                mesh.add_triangle({VertexData{CUBE_VERTICES[CUBE_INDICES[i] * 8] + cell.first.first,
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 1] + y,
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 2] + cell.first.second,
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 3],
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 4],
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 5],
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 6],
                                              CUBE_VERTICES[CUBE_INDICES[i] * 8 + 7]}
                                  },
                                  {VertexData{CUBE_VERTICES[CUBE_INDICES[i + 1] * 8] + cell.first.first,
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 1] + y,
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 2] + cell.first.second,
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 3],
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 4],
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 5],
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 6],
                                              CUBE_VERTICES[CUBE_INDICES[i + 1] * 8 + 7]}
                                  },
                                  {VertexData{CUBE_VERTICES[CUBE_INDICES[i + 2] * 8] + cell.first.first,
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 1] + y,
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 2] + cell.first.second,
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 3],
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 4],
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 5],
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 6],
                                              CUBE_VERTICES[CUBE_INDICES[i + 2] * 8 + 7]}
                                  }
                );
            }
        }
    }

    dirty = false;
    return
            mesh;
}

