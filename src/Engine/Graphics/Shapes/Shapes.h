#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include "../Texture/Texture.h"
#include "../Video/Shader/Shader.h"

namespace Hjalmari7 {
    namespace Shapes {
        class Shape_t {
        public:
            Shape_t::Shape_t(   const std::vector<float>& vertices,
                                const std::vector<GLuint>& indices,
                                GLuint shader,
                                Texture_t* texture,
                                const std::vector<int>& attributes) : indices(indices), shader(shader), texture(texture) 
            {
                // Generate the VAO using the utility function
                this->VAO = Video::GenerateVertexObjects_f(vertices, indices, attributes);
            }

            void Draw();

        private:
            GLuint VAO;                 // Vertex Array Object
            GLuint shader;              // Shader program ID
            Texture_t* texture;         // Texture
            std::vector<GLuint> indices; // Indices for drawing
        };

        Shape_t Rectangle_S(float xscale, float yscale, GLuint shader, Texture_t* texture);
        Shape_t Square_S(float scale, GLuint shader, Texture_t* texture);
    }
}

#endif // SHAPES_H
