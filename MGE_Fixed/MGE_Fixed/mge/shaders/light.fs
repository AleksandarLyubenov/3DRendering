#version 400

in vec2 texCoord;
in vec3 fragNormal;
in vec3 fragPosition;

uniform sampler2D diffuseTexture;

uniform vec3 ambientLightColor;
uniform float ambientIntensity;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform vec3 cameraPosition;
uniform float shininess;     

uniform float c1; // Constant attenuation
uniform float c2; // Linear attenuation
uniform float c3; // Quadratic attenuation

out vec4 fragColor;

void main() {
    // Normalized vectors
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Ambient 
    vec3 ambient = ambientLightColor * ambientIntensity * diffuseColor;

    // Diffuse 
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lightColor * diffuseColor * diff;

    // Specular 
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
    vec3 specular = specularColor * spec * diffuseColor;

    // Attenuation
    float distance = length(lightPosition - fragPosition);
    float attenuation = 1.0 / (c1 + c2 * distance + c3 * distance * distance);

    vec3 result = ambient + (diffuse + specular) * attenuation;

    // Apply to texture
    vec4 textureColor = texture(diffuseTexture, texCoord);
    fragColor = vec4(result * textureColor.rgb, textureColor.a);
}
