//
// Created by simone on 10/06/25.
//

#include "chunk.hpp"

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
    mesh.clear();
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
            for (int i = 0; i < CUBE_VERTICES.size(); i += VERTEX_DATA_SIZE * 3) {
                mesh.add_triangle({VertexData{CUBE_VERTICES[i] + cell.first.first,
                                              CUBE_VERTICES[i + 1] + y,
                                              CUBE_VERTICES[i + 2] + cell.first.second,
                                              CUBE_VERTICES[i + 3],
                                              CUBE_VERTICES[i + 4],
                                              CUBE_VERTICES[i + 5],
                                              CUBE_VERTICES[i + 6],
                                              CUBE_VERTICES[i + 7]}
                                  },
                                  {VertexData{CUBE_VERTICES[i + 8] + cell.first.first,
                                              CUBE_VERTICES[i + 9] + y,
                                              CUBE_VERTICES[i + 10] + cell.first.second,
                                              CUBE_VERTICES[i + 11],
                                              CUBE_VERTICES[i + 12],
                                              CUBE_VERTICES[i + 13],
                                              CUBE_VERTICES[i + 14],
                                              CUBE_VERTICES[i + 15]}
                                  },
                                  {VertexData{CUBE_VERTICES[i + 16] + cell.first.first,
                                              CUBE_VERTICES[i + 17] + y,
                                              CUBE_VERTICES[i + 18] + cell.first.second,
                                              CUBE_VERTICES[i + 19],
                                              CUBE_VERTICES[i + 20],
                                              CUBE_VERTICES[i + 21],
                                              CUBE_VERTICES[i + 22],
                                              CUBE_VERTICES[i + 23]}
                                  }
                );
            }
        }
    }
    mesh.create();
    dirty = false;
    return mesh;
}

