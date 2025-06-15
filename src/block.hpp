//
// Created by simone on 14/06/25.
//

#ifndef MINECRAFT_BLOCK_HPP
#define MINECRAFT_BLOCK_HPP

const std::vector<float> CUBE_VERTICES = {
        // Front face
        -0.5f, -0.5f, 0.5f, 0, 0, 1, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0, 0, 1, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0, 0, 1, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0, 0, 1, 0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 0, 0, -1, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0, 0, -1, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0, 0, -1, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0, 0, -1, 1.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, -1, 0, 0, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1, 0, 0, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1, 0, 0, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, -1, 0, 0, 0.0f, 1.0f,

        // Right face
        0.5f, -0.5f, -0.5f, 1, 0, 0, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1, 0, 0, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1, 0, 0, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1, 0, 0, 1.0f, 1.0f,

        // Top face
        -0.5f, 0.5f, 0.5f, 0, 1, 0, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0, 1, 0, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0, 1, 0, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0, 1, 0, 0.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, 0.5f, 0, -1, 0, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0, -1, 0, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0, -1, 0, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0, -1, 0, 0.0f, 1.0f,
};
const std::vector<int> CUBE_INDICES = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20
};

struct VertexData {
    // position(x, y, z), normal(x, y, z), texcoord(u, v)
    float position_x;
    float position_y;
    float position_z;
    float normal_x;
    float normal_y;
    float normal_z;
    float tex_u;
    float tex_v;

    bool operator==(const VertexData &other) const {
        return position_x == other.position_x &&
               position_y == other.position_y &&
               position_z == other.position_z &&
               normal_x == other.normal_x &&
               normal_y == other.normal_y &&
               normal_z == other.normal_z &&
               tex_u == other.tex_u &&
               tex_v == other.tex_v;
    }

    // Member hash function
    std::size_t hash() const {
        std::size_t h1 = std::hash<float>{}(position_x);
        std::size_t h2 = std::hash<float>{}(position_y);
        std::size_t h3 = std::hash<float>{}(position_z);
        std::size_t h4 = std::hash<float>{}(normal_x);
        std::size_t h5 = std::hash<float>{}(normal_y);
        std::size_t h6 = std::hash<float>{}(normal_z);
        std::size_t h7 = std::hash<float>{}(tex_u);
        std::size_t h8 = std::hash<float>{}(tex_v);
        return (((((((h1 ^ (h2 << 1)) ^ (h3 << 1)) ^ (h4 << 1))
                   ^ (h5 << 1)) ^ (h6 << 1)) ^ (h7 << 1)) ^ (h8 << 1));
    }
};

namespace std {
    template<>
    struct hash<VertexData> {
        std::size_t operator()(const VertexData &v) const {
            return v.hash();  // Delegates to member function
        }
    };
}

#endif //MINECRAFT_BLOCK_HPP
