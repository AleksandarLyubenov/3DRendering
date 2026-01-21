#version 330 core

uniform float rotationSpeedX; // Horizontal rotation speed
uniform float rotationSpeedY; // Vertical rotation speed

layout(location = 0) in vec3 aPos; // Vertex position

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
