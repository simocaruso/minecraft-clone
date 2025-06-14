//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_RENDERING_SYSTEM_HPP
#define MINECRAFT_RENDERING_SYSTEM_HPP


#include <GLFW/glfw3.h>
#include "system.hpp"
#include "shader.hpp"
#include "../timer.hpp"

class RenderingSystem : public System {
public:
    explicit RenderingSystem(entt::registry &registry);

    void update(int elapsed) override;

private:
    Shader shader = Shader("vtx", "frag");
    Timer toggled_render_mode;

    void init_window();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void toggle_render_mode();
};


#endif //MINECRAFT_RENDERING_SYSTEM_HPP
