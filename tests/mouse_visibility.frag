#version 130

uniform sampler2D texture;
uniform vec2 mousePos;      // Mouse position in normalized coordinates
uniform float radius;       // Radius of the area to show
uniform vec2 aspectRatio;   // Aspect ratio (x, y)

void main()
{
    // Get the current texture coordinates
    vec2 texCoords = gl_TexCoord[0].xy;

    // Calculate the distance from the mouse position using the aspect ratios
    float distX = (texCoords.x - mousePos.x) / aspectRatio.y;
    float distY = (texCoords.y - mousePos.y) / aspectRatio.x;
    float distance = sqrt(distX * distX + distY * distY);

    // Only show texture if within the specified radius
    if (distance > radius)
        discard; // Discard the fragment if outside the radius

    gl_FragColor = texture2D(texture, texCoords); // Set the fragment color
}
