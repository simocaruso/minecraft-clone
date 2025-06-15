#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
uniform sampler2D atlas;

const int tile_x = 0;
const int tile_y = 15;
const float tile_size = 16.0f;
const float atlas_size = 256.0f;


void main() {
    float threshold = 0.01; // tweak as needed
    float is_lateral_face = max(
        step(threshold, abs(Normal.x)),
        step(threshold, abs(Normal.z))
    );
    float is_down_face = step(threshold, -1 * Normal.y) * 2;
    vec2 atlas_offset = vec2((is_lateral_face + is_down_face + tile_x) * tile_size / atlas_size,
                            tile_y * tile_size / atlas_size);
    vec2 atlas_scale  = vec2(tile_size / atlas_size, tile_size / atlas_size);
    FragColor = texture(atlas, atlas_offset + (TexCoord * atlas_scale));
}