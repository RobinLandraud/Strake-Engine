#version 330 core

void main() {
    // We don't care about the color, just write depth into the shadow map
    gl_FragDepth = gl_FragCoord.z; // Write depth into the depth buffer
}