//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_SHADER_HPP
#define MINECRAFT_SHADER_HPP


#include <string>
#include "glm/glm.hpp"

class Shader {
public:
    Shader(const std::string &vtx, const std::string &frag);

    void init();

    void use() const;

    void set_bool(const std::string &name, bool value) const;

    void set_int(const std::string &name, int value) const;

    void set_float(const std::string &name, float value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int program{};
    std::string vtx_source;

    std::string frag_source;
};


#endif //MINECRAFT_SHADER_HPP
