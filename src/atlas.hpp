//
// Created by simone on 14/06/25.
//

#ifndef MINECRAFT_ATLAS_HPP
#define MINECRAFT_ATLAS_HPP


class AtlasLoader {
public:
    ~AtlasLoader();
    void load();
    void free();
    int width{};
    int height{};
    unsigned char *data = nullptr;
private:
    int n_channels{};
};


#endif //MINECRAFT_ATLAS_HPP
