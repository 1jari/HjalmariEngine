#version 330 core

// Input vertex data (from the vertex buffer object)
layout(location = 0) in vec3 aPos; // Position
layout(location = 1) in vec3 aColor; // Color
layout(location = 2) in vec2 aTexCoord; // Texture coordinates

// Output data to the fragment shader
out vec3 vertexColor; 
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Pass the color and texture coordinates to the fragment shader
    vertexColor = aColor;
    texCoord = aTexCoord;

    // Apply transformation using the model, view, and projection matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
