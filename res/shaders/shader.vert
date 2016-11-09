#version 150

// in vec2 camera_pos;
in vec2 entity_pos;
in vec2 tex_coord;
out vec2 v_tex_coord;
void main() {
    gl_Position = vec4(entity_pos, 0.0, 1.0);
    gl_Position.x /= 640;
    gl_Position.y /= 480;

    v_tex_coord = tex_coord;
}