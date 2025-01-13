#include "SOIL/SOIL.h"
#include "Texture.h"  // Make sure Texture.h is correctly referenced

namespace Hjalmari7 {

Texture_t::Texture_t(const std::string& filepath, GLuint program) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;

    // Load the image using SOIL
    unsigned char* image = SOIL_load_image(filepath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if (image == nullptr) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
        throw std::runtime_error("Texture loading failed");
    }

    // Determine the format based on the number of channels
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    // Generate the texture using OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image data after uploading to OpenGL
    SOIL_free_image_data(image);

    // Cache the uniform location for efficiency
    textureLoc = glGetUniformLocation(program, "texture1");
    if (textureLoc == -1) {
        std::cerr << "Failed to find texture1 uniform location" << std::endl;
    }
}

Texture_t::~Texture_t() {
    glDeleteTextures(1, &ID);
}

void Texture_t::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    if (textureLoc != -1) {
        glUniform1i(textureLoc, 0);
    }
}

}
