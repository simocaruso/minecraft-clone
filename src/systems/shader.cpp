//
// Created by simone on 08/06/25.
//

#include <iostream>
#include "glad/glad.h"
#include "shader.hpp"
#include "../file_manager.hpp"
#include "../atlas.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "system.hpp"

Shader::Shader(const std::string &vtx, const std::string &frag) {
    vtx_source = FileManager::load_text_file("shader", vtx, "glsl");
    frag_source = FileManager::load_text_file("shader", frag, "glsl");
}

void Shader::init() {
    unsigned int vtx_shader;
    vtx_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vtx_source_ptr = vtx_source.c_str();
    glShaderSource(vtx_shader, 1, &vtx_source_ptr, NULL);
    glCompileShader(vtx_shader);

    unsigned int frag_shader;
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *frag_source_ptr = frag_source.c_str();
    glShaderSource(frag_shader, 1, &frag_source_ptr, NULL);
    glCompileShader(frag_shader);

    program = glCreateProgram();
    glAttachShader(program, vtx_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    glDeleteShader(vtx_shader);
    glDeleteShader(frag_shader);

    load_atlas();
    use();
    auto projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
    setMat4("projection", projection);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Shader::use() const {
    glUseProgram(program);
}

void Shader::set_bool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int) value);
}

void Shader::set_int(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::load_atlas() {
    AtlasLoader atlas_loader;
    atlas_loader.load();
    glGenTextures(1, &atlas);
    glBindTexture(GL_TEXTURE_2D, atlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlas_loader.width, atlas_loader.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 atlas_loader.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    atlas_loader.free();
}
