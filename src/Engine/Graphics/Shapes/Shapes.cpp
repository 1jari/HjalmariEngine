#include "Shapes.h"
#include <iostream>
#include <vector>

namespace Hjalmari7 {
    namespace Shapes {

        // Method to draw the shape
        void Shape_t::Draw() {
            // Ensure the shader program is active
            glUseProgram(shader);

            // Bind the texture if it exists
            if (texture) {
                texture->bind();
            }

            // Bind the Vertex Array Object and draw the shape
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }

        // Factory function to create a rectangle shape
        Shape_t Rectangle_S(float xscale, float yscale, GLuint shader, Texture_t* texture) {
            // Define rectangle vertices: position (3), color (3), texture coordinates (2)
            std::vector<float> vertices = {
                // Positions            // Colors               // Texture coordinates
                -xscale, -yscale,  0.0f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Bottom-left
                 xscale, -yscale,  0.0f,  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Bottom-right
                -xscale,  yscale,  0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 1.0f, // Top-left
                 xscale,  yscale,  0.0f,  1.0f, 1.0f, 0.0f,    1.0f, 1.0f  // Top-right
            };

            // Define the indices for the two triangles that make up the rectangle
            std::vector<GLuint> indices = {
                0, 1, 2,  // First triangle
                1, 2, 3   // Second triangle
            };

            // Return a Shape_t object initialized with the vertices, indices, shader, texture, and attribute sizes
            return Shape_t(vertices, indices, shader, texture, {3, 3, 2});
        }

        Shape_t Square_S(float scale, GLuint shader, Texture_t* texture) {
            return Rectangle_S(scale, scale, shader, texture);
        }

    } // namespace Shapes
} // namespace Hjalmari7
