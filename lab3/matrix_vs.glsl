#version 400
in vec3 vertex_position;
in vec3 vertex_colour;
uniform mat4 MVP;
flat out vec3 colour;
void main ()
{
colour = vertex_colour;
gl_Position = MVP * vec4 (vertex_position, 1.0);
}