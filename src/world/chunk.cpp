//
// Created by simone on 10/06/25.
//

#include <stdexcept>
#include "chunk.hpp"

const std::vector<float> CUBE_VERTICES = {
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,

        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1
};
const std::vector<int> CUBE_INDICES = {
        1, 0, 3, 1, 3, 2, // north (-z)
        4, 5, 6, 4, 6, 7, // south (+z)
        5, 1, 2, 5, 2, 6, // east (+x)
        0, 4, 7, 0, 7, 3, // west (-x)
        2, 3, 7, 2, 7, 6, // top (+y)
        5, 4, 0, 5, 0, 1, // bottom (-y)
};

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
                mesh.add_triangle({CUBE_VERTICES[CUBE_INDICES[i] * 3] + cell.first.first,
                                   CUBE_VERTICES[CUBE_INDICES[i] * 3 + 1] + y,
                                   CUBE_VERTICES[CUBE_INDICES[i] * 3 + 2] + cell.first.second},
                                  {CUBE_VERTICES[CUBE_INDICES[i + 1] * 3] + cell.first.first,
                                   CUBE_VERTICES[CUBE_INDICES[i + 1] * 3 + 1] + y,
                                   CUBE_VERTICES[CUBE_INDICES[i + 1] * 3 + 2] + cell.first.second},
                                  {CUBE_VERTICES[CUBE_INDICES[i + 2] * 3] + cell.first.first,
                                   CUBE_VERTICES[CUBE_INDICES[i + 2] * 3 + 1] + y,
                                   CUBE_VERTICES[CUBE_INDICES[i + 2] * 3 + 2] + cell.first.second}
                );
            }
        }
    }
    dirty = false;
    return mesh;
}

