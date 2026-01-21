#version 400

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal; // Original normal
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform sampler2D heightMap;

out vec2 fragUV;
out vec3 fragNormal;   // Recalculated normal
out vec3 fragPosition; 

void main() {
    float height = texture(heightMap, uv).r;
    vec3 position = vertex;
    position.y += height * 10.0;

    float offset = 0.01; // Small UV offset for sampling
    float heightL = texture(heightMap, uv + vec2(-offset, 0.0)).r;
    float heightR = texture(heightMap, uv + vec2(offset, 0.0)).r;
    float heightD = texture(heightMap, uv + vec2(0.0, -offset)).r;
    float heightU = texture(heightMap, uv + vec2(0.0, offset)).r;


    // Everything below is fixing up the normals for the directional light


    vec3 tangentX = vec3(2.0 * offset, (heightR - heightL) * 10.0, 0.0);
    vec3 tangentZ = vec3(0.0, (heightU - heightD) * 10.0, 2.0 * offset);

    vec3 normalCalculated = normalize(cross(tangentZ, tangentX));

    fragPosition = vec3(modelMatrix * vec4(position, 1.0));
    fragNormal = mat3(transpose(inverse(modelMatrix))) * normalCalculated;

    gl_Position = projectionMatrix * viewMatrix * vec4(fragPosition, 1.0);
    fragUV = uv;
}