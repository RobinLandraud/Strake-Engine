#version 330 core

struct Light {
    vec3 position;  // Position de la lumière
    vec3 color;     // Couleur de la lumière
    float intensity; // Intensité de la lumière
};

uniform Light light;                // Light properties
uniform sampler2D textureSampler;   // Texture sampler
uniform vec3 viewPos;               // Camera position
uniform float alphaThreshold;       // Alpha threshold
uniform float shininess;            // Shininess factor
uniform float ambientIntensity;     // Intensité de la lumière ambiante minimale

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
    vec3 lightDir = normalize(light.position - FragPos); // Get the light direction

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0); // Calculate the diffuse factor
    vec3 diffuse = light.color * diff; // Calculate the diffuse color

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos); // Get the view direction
    vec3 reflectDir = reflect(-lightDir, normal); // Get the reflection direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Calculate the specular factor
    // Shininess is set to 32 (between 0 and 256)
    vec3 specular = light.color * spec; // Calculate the specular color

    // Ambient lighting
    vec3 ambient = ambientIntensity * light.color; // Calculate the ambient color

    vec3 lighting = (diffuse + specular) * light.intensity + ambient; // Calculate the lighting
    vec3 finalColor = texColor.rgb * lighting; // Calculate the final color
    FragColor = vec4(finalColor, texColor.a); // Output the final color
}
