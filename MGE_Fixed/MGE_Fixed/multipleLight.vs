#version 400

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 mvpMatrix;

out vec2 texCoord;
out vec3 fragNormal;
out vec3 fragPosition;

void main() {
    gl_Position = mvpMatrix * vec4(vertex, 1.0);
    texCoord = uv;
    fragNormal = normal;
    fragPosition = vertex;
}
