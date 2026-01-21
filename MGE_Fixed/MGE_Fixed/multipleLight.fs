#version 400

#define MAX_LIGHTS 10

in vec2 texCoord;
in vec3 fragNormal;
in vec3 fragPosition;

uniform sampler2D diffuseTexture;

uniform vec3 ambientLightColor;
uniform float ambientIntensity;

out vec4 fragColor;

uniform int lightCount; // Number of lights
uniform vec3 lightPositions[10]; // Array of light positions
uniform vec3 lightColors[10]; // Array of light colors


void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(-fragPosition); // Assume the camera is at the origin
    vec3 resultColor = ambientLightColor * ambientIntensity;

    for(int i = 0; i < lightCount; i++) {
        vec3 lightDir = normalize(lightPositions[i] - fragPosition);
        float diff = max(dot(lightDir, normalize(fragNormal)), 0.0);
        vec3 diffuse = lightColors[i] * diff;
        result += diffuse; // Simplified, add specular, attenuation, etc.
    }

    vec4 textureColor = texture(diffuseTexture, texCoord);
    fragColor = vec4(resultColor * textureColor.rgb, textureColor.a);
}
