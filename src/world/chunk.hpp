//
// Created by simone on 10/06/25.
//

#ifndef MINECRAFT_CHUNK_HPP
#define MINECRAFT_CHUNK_HPP


#include <map>
#include "../mesh.hpp"

class Chunk {
public:
    Chunk();

    Mesh get_mesh();

private:
    const int SIZE = 16;
    const int MAX_HEIGHT = 10;
    std::map<std::pair<int, int>, int> height_map;
    Mesh mesh;
    bool dirty = true;

    void generate();
};


#endif //MINECRAFT_CHUNK_HPP
