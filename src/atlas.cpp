//
// Created by simone on 14/06/25.
//

#include <iostream>
#include "atlas.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "file_manager.hpp"

void AtlasLoader::load() {
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(FileManager::get_file_path("res", "blocks", "png").c_str(), &width, &height, &n_channels, 0);
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
    }
}

AtlasLoader::~AtlasLoader() {
    free();
}

void AtlasLoader::free() {
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }
}
