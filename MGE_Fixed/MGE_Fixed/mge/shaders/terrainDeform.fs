#version 400

in vec2 fragUV;
in vec3 fragNormal;  
in vec3 fragPosition; 

uniform sampler2D splatMap;    
uniform sampler2D diffuse1;    
uniform sampler2D diffuse2;    
uniform sampler2D diffuse3;    
uniform sampler2D diffuse4;    

uniform vec3 lightDirection;   
uniform vec3 lightColor;       
uniform vec3 ambientColor;     

out vec4 fragColor;

void main() {
vec3 N = normalize(fragNormal);
fragColor = vec4(N * 0.5 + 0.5, 1.0); // Map [-1, 1] to [0, 1] for RGB display
}

// Normal visualisation
//void main() {
//    vec3 N = normalize(fragNormal);
//    fragColor = vec4(N * 0.5 + 0.5, 1.0); // Map [-1, 1] to [0, 1] for RGB display
//}

// Normal Recalculation inside the .fs instead of .vs
//#version 400
//
//in vec2 fragUV;
//in vec3 fragPosition;
//
//uniform sampler2D heightMap;
//
//uniform sampler2D splatMap;
//uniform sampler2D diffuse1;
//uniform sampler2D diffuse2;
//uniform sampler2D diffuse3;
//uniform sampler2D diffuse4;
//
//uniform vec3 lightDirection;
//uniform vec3 lightColor;
//uniform vec3 ambientColor;
//
//out vec4 fragColor;
//
//void main() {
//    float offset = 0.001;
//
//    // Sample heightmap for normal recalculation
//    float height = texture(heightMap, fragUV).r;
//    float heightL = texture(heightMap, fragUV + vec2(-offset, 0.0)).r;
//    float heightR = texture(heightMap, fragUV + vec2(offset, 0.0)).r;
//    float heightD = texture(heightMap, fragUV + vec2(0.0, -offset)).r;
//    float heightU = texture(heightMap, fragUV + vec2(0.0, offset)).r;
//
//    vec3 tangentX = vec3(2.0 * offset, (heightR - heightL) * 10.0, 0.0);
//    vec3 tangentZ = vec3(0.0, (heightU - heightD) * 10.0, 2.0 * offset);
//
//    vec3 normalCalculated = normalize(cross(tangentZ, tangentX));
//
//    // Sample splat map and textures
//    vec4 splat = texture(splatMap, fragUV);
//    vec4 tex1 = texture(diffuse1, fragUV);
//    vec4 tex2 = texture(diffuse2, fragUV);
//    vec4 tex3 = texture(diffuse3, fragUV);
//    vec4 tex4 = texture(diffuse4, fragUV);
//
//    vec4 blendedColor = splat.r * tex1 + 
//                        splat.g * tex2 + 
//                        splat.b * tex3 + 
//                        splat.a * tex4;
//
//    // Lighting calculations
//    vec3 N = normalCalculated; // Use per-fragment normal
//    vec3 L = normalize(-lightDirection);
//
//    float diffuseIntensity = max(dot(N, L), 0.0);
//
//    vec3 lighting = ambientColor + (lightColor * diffuseIntensity);
//
//    vec3 finalColor = blendedColor.rgb * lighting;
//
//    fragColor = vec4(finalColor, blendedColor.a);
//}