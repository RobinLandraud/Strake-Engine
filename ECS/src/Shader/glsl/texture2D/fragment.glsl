#version 330 core

struct Light {
    int type;        // 0 = directional, 1 = point
    vec3 color;      // Color of the light
    float intensity; // Intensity of the light
    float ambient;   // Minimal intensity of the light (doesn't depend on distance)
    vec3 position;   // Only for point lights
    vec3 direction;  // Only for directional lights
};

// Lights
uniform Light lights[8];           // Array of light properties (up to 8 lights)
uniform int numLights;             // Number of active lights

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
        if (lights[i].type == 0) {
            // Directional light
            lightDir = normalize(-lights[i].direction); // Direction is fixed
        } else if (lights[i].type == 1) {
            // Point light
            lightDir = normalize(lights[i].position - FragPos); // Direction from the light to the fragment
        }

        // Diffuse lighting
        float diff = max(dot(normal, lightDir), 0.0); // Diffuse factor
        totalDiffuse += lights[i].color * diff * lights[i].intensity; // Accumulate diffuse color

        // Specular lighting
        vec3 viewDir = normalize(viewPos - FragPos); // View direction
        vec3 reflectDir = reflect(-lightDir, normal); // Reflection direction
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Specular factor
        totalSpecular += lights[i].color * spec * lights[i].intensity; // Accumulate specular color

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
