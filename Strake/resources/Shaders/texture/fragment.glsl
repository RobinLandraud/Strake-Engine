#version 330 core

struct Light {
    int type;        // 0 = directional, 1 = point
    vec3 color;      // Color of the light
    float intensity; // Intensity of the light
    float ambient;   // Minimal intensity of the light (doesn't depend on distance)
    vec3 position;   // Only for point lights
    vec3 direction;  // Only for directional lights
    mat4 lightSpaceMatrix; // Light's view-projection matrix (for shadow mapping)
    int shadowIndex;       // Index of the shadow map in the shadowMaps array (for shadow mapping, directional lights only)
};

// Lights
uniform int numLights;             // Number of active lights
uniform Light lights[8];           // Array of light properties (up to 8 lights)
uniform sampler2D shadowMaps[8];        // Shadow map texture
// Camera
uniform vec3 viewPos;              // Camera position

// Object
uniform sampler2D textureSampler;  // Texture sampler
uniform float alphaThreshold;      // Alpha threshold
uniform float shininess;           // Shininess factor of object
uniform float minIntensity;        // Minimum intensity on object (doesn't depend on distance)

in vec2 TexCoords;        // Texture coordinates from the vertex shader
in vec3 FragPos;          // Fragment position in world space
in vec3 Normal;           // Normal in world space

out vec4 FragColor;       // Output fragment color

float calculateShadow(vec4 fragPosLightSpace, sampler2D shadowMap, vec3 lightDir, vec3 normal) {

    int kernelSize = 2; // Size of the kernel (for PCF)
    float maxBias = 0.001; // Maximum bias for the shadow calculation
    float minBias = 0.0005; // Minimum bias for the shadow calculation

    // Perspective divide to get normalized light-space coordinates
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5; // Transform to [0, 1]
    projCoords = clamp(projCoords, 0.0, 1.0);

    // Sample depth from shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // Compute the angle between the light direction and the surface normal
    float angle = abs(dot(normal, lightDir));
    angle = clamp(angle, 0.0, 1.0); // Clamp the angle between 0 and 1

    // Adjust bias based on the angle (Slop Scale Depth Bias)
    float bias = max(maxBias * (1.0 - angle), minBias); // Bias based on angle

    float shadow = 0.0; // Default shadow factor
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0); // Size of a texel, meaning the size of a pixel in the shadow map
    // Iterate through the kernel and calculate the shadow factor (PCF)
    for (int x = -kernelSize; x <= kernelSize; x++) {
        for (int y = -kernelSize; y <= kernelSize; y++) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += (currentDepth - bias) > pcfDepth ? 0.0 : 1.0;
        }
    }

    // Check if the fragment is in shadow
    return shadow / pow(2.0 * float(kernelSize) + 1.0, 2.0);
}


void main() {
    vec4 texColor = texture(textureSampler, TexCoords); // Get the texture color
    if (texColor.a < alphaThreshold) {
        discard; // Discard the fragment if the alpha value is below the threshold
    }

    vec3 normal = normalize(Normal); // Normalize the normal
    vec3 totalDiffuse = vec3(0.0);   // Initialize diffuse component
    vec3 totalSpecular = vec3(0.0);  // Initialize specular component
    float maxAmbient = 0.0;          // Maximum ambient contribution

    // Iterate through each light and calculate its contribution
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float shadow = 1.0; // Default shadow factor

        if (lights[i].type == 0) {
            // Directional light
            lightDir = normalize(-lights[i].direction); // Direction is fixed
            vec4 fragPosLightSpace = lights[i].lightSpaceMatrix * vec4(FragPos, 1.0); // GOOD - Transform fragment position to light space
            shadow = calculateShadow(fragPosLightSpace, shadowMaps[0], lightDir, normal); // Calculate shadow factor
        } else if (lights[i].type == 1) {
            // Point light
            lightDir = normalize(lights[i].position - FragPos); // Direction from the light to the fragment
        }

        // Diffuse lighting
        float diff = max(dot(normal, lightDir), 0.0); // Diffuse factor
        totalDiffuse += lights[i].color * diff * lights[i].intensity * shadow; // Accumulate diffuse color

        // Specular lighting
        vec3 viewDir = normalize(viewPos - FragPos); // View direction
        vec3 reflectDir = reflect(-lightDir, normal); // Reflection direction
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Specular factor
        totalSpecular += lights[i].color * spec * lights[i].intensity * shadow; // Accumulate specular color

        // Ambient lighting
        maxAmbient = max(maxAmbient, lights[i].ambient); // Keep the maximum ambient value
    }

    // Combine ambient lighting
    maxAmbient = max(minIntensity, maxAmbient); // Ensure ambient lighting meets the minimum threshold
    vec3 ambient = maxAmbient * vec3(1.0);      // Apply uniform ambient light

    // Final lighting
    vec3 lighting = totalDiffuse + totalSpecular + ambient; // Total lighting
    vec3 finalColor = texColor.rgb * lighting;              // Apply lighting to texture color

    FragColor = vec4(finalColor, texColor.a); // Output the final color
}
