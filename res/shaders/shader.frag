#version 150

in vec2 v_tex_coord;
out vec4 colour;
out vec2 out_tex_coord;
uniform sampler2D tex;
void main() {
    colour = texture(tex, v_tex_coord / textureSize(tex, 0));
}