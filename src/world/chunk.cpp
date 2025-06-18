//
// Created by simone on 10/06/25.
//

#include <iostream>
#include "chunk.hpp"
#include "chunk_manager.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/RederingComponent.hpp"

Chunk::Chunk(int size, glm::ivec3 in_world_position, entt::registry &registry) : size(size),
                                                                                 in_world_position(in_world_position),
                                                                                 registry(registry) {
    generate();
    entity = registry.create();
    auto &transform_component = registry.emplace<TransformComponent>(entity);
    auto &rendering_component = registry.emplace<RenderingComponent>(entity);
    transform_component.position = in_world_position;
}

void Chunk::generate() {
    srandom(time(nullptr));
    for (int x = 0; x < size; x++) {
        for (int z = 0; z < size; z++) {
            height_map[std::make_pair(x, z)] = random() % MAX_HEIGHT;
        }
    }
}


void Chunk::update_mesh(ChunkManager &chunk_manager) {
    auto add_face = [](CUBE_FACE_IDX face, Mesh &mesh, int x_off_set, int y_off_set, int z_off_set) {
        auto start_idx = face * VERTEX_DATA_SIZE * 6;
        for (int i = start_idx; i < start_idx + VERTEX_DATA_SIZE * 6; i += VERTEX_DATA_SIZE * 3) {
            mesh.add_triangle({VertexData{CUBE_VERTICES[i] + x_off_set,
                                          CUBE_VERTICES[i + 1] + y_off_set,
                                          CUBE_VERTICES[i + 2] + z_off_set,
                                          CUBE_VERTICES[i + 3],
                                          CUBE_VERTICES[i + 4],
                                          CUBE_VERTICES[i + 5],
                                          CUBE_VERTICES[i + 6],
                                          CUBE_VERTICES[i + 7]}
                              },
                              {VertexData{CUBE_VERTICES[i + 8] + x_off_set,
                                          CUBE_VERTICES[i + 9] + y_off_set,
                                          CUBE_VERTICES[i + 10] + z_off_set,
                                          CUBE_VERTICES[i + 11],
                                          CUBE_VERTICES[i + 12],
                                          CUBE_VERTICES[i + 13],
                                          CUBE_VERTICES[i + 14],
                                          CUBE_VERTICES[i + 15]}
                              },
                              {VertexData{CUBE_VERTICES[i + 16] + x_off_set,
                                          CUBE_VERTICES[i + 17] + y_off_set,
                                          CUBE_VERTICES[i + 18] + z_off_set,
                                          CUBE_VERTICES[i + 19],
                                          CUBE_VERTICES[i + 20],
                                          CUBE_VERTICES[i + 21],
                                          CUBE_VERTICES[i + 22],
                                          CUBE_VERTICES[i + 23]}
                              }
            );
        }
    };
    Mesh mesh;
    for (auto &[coords, max_height]: height_map) {
        auto x = coords.first;
        auto z = coords.second;
        for (int y = 0; y <= max_height; y++) {
            if ((!chunk_manager.is_solid({in_world_position.x + x,
                                          in_world_position.y + y + 1,
                                          in_world_position.z + z})) ) {
                add_face(TOP, mesh, x, y, z);
            }
            if (!chunk_manager.is_solid({in_world_position.x + x,
                                         in_world_position.y + y - 1,
                                         in_world_position.z + z})) {
                add_face(BOTTOM, mesh, x, y, z);
            }
            if (!chunk_manager.is_solid({in_world_position.x + x + 1,
                                         in_world_position.y + y,
                                         in_world_position.z + z})) {
                add_face(RIGHT, mesh, x, y, z);
            }
            if (!chunk_manager.is_solid({in_world_position.x + x - 1,
                                         in_world_position.y + y,
                                         in_world_position.z + z})) {
                add_face(LEFT, mesh, x, y, z);
            }
            if (!chunk_manager.is_solid({in_world_position.x + x,
                                         in_world_position.y + y,
                                         in_world_position.z + z + 1})) {
                add_face(FRONT, mesh, x, y, z);
            }
            if (!chunk_manager.is_solid({in_world_position.x + x,
                                         in_world_position.y + y,
                                         in_world_position.z + z - 1})) {
                add_face(BACK, mesh, x, y, z);
            }
        }
    }
    mesh.create();
    auto &rendering_component = registry.get<RenderingComponent>(entity);
    rendering_component.mesh = mesh;
}

bool Chunk::is_solid(glm::ivec3 position) {
    return position.y <= height_map[std::make_pair(position.x, position.z)];
}
