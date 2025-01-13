#version 330 core

in vec3 vertexColor; // Color passed from vertex shader
in vec2 texCoord; // Texture coordinates passed from vertex shader

out vec4 FragColor;

uniform sampler2D texture1; // The texture sampler

void main() {
    // Sample the texture using the texture coordinates
    vec4 texColor = texture(texture1, texCoord);

    // Combine the texture color with the vertex color (for coloring with the texture)
    FragColor = texColor; //* vec4(vertexColor, 1.0);
}
