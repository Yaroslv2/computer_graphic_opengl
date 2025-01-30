#version 400
in vec3 vertex_position;
in vec3 vertex_color;

out vec3 f_pos;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    f_pos = vec3(model * vec4(vertex_position, 1.0));
    color = vertex_color;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}