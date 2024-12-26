#version 330 core

struct Light {
    vec3 position;  // Position of the light
    vec3 color;     // Color of the light
    float intensity; // Intensity of the light
};

uniform Light lights[8];           // Array of light properties (up to 8 lights)
uniform int numLights;             // Number of active lights
uniform sampler2D textureSampler;  // Texture sampler
uniform vec3 viewPos;              // Camera position
uniform float alphaThreshold;      // Alpha threshold
uniform float shininess;           // Shininess factor
uniform float ambientIntensity;    // Minimum ambient light intensity

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

    // Iterate through each light and calculate its contribution
    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - FragPos); // Light direction

        // Diffuse lighting
        float diff = max(dot(normal, lightDir), 0.0); // Diffuse factor
        totalDiffuse += lights[i].color * diff * lights[i].intensity; // Accumulate diffuse color

        // Specular lighting
        vec3 viewDir = normalize(viewPos - FragPos); // View direction
        vec3 reflectDir = reflect(-lightDir, normal); // Reflection direction
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Specular factor
        totalSpecular += lights[i].color * spec * lights[i].intensity; // Accumulate specular color
    }

    // Ambient lighting
    vec3 ambient = ambientIntensity * vec3(1.0); // Uniform ambient light

    vec3 lighting = totalDiffuse + totalSpecular + ambient; // Total lighting
    vec3 finalColor = texColor.rgb * lighting; // Apply lighting to texture color

    FragColor = vec4(finalColor, texColor.a); // Output the final color
}