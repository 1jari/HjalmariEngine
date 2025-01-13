#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  // For transformations
#include <glm/gtc/type_ptr.hpp>  // To pass matrices as pointers

#include "./Engine/Engine.h"
#include "./Engine/IO/Files.h"
#include "./Engine/Graphics/Shapes/Shapes.h"
#include "./Engine/Graphics/Video/Shader/Shader.h"
#include "./Engine/Graphics/Texture/Texture.h"

using namespace Hjalmari7;

int main(int argc, char* argv[]) {
    // Initialize the engine with a window
    std::unique_ptr<Engine> engine = std::make_unique<Engine>("jogo!", 1280, 720);

    // Load and compile shaders
    const std::string vertexShaderSource = FileSystem::ReadFile_f("./files/glsl/texture.vs");
    const std::string fragmentShaderSource = FileSystem::ReadFile_f("./files/glsl/texture.fs");

    GLuint vertexShader = Video::CompileShader_f(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    if (vertexShader == 0) return -1;

    GLuint fragShader = Video::CompileShader_f(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
    if (fragShader == 0) {
        glDeleteShader(vertexShader);
        return -1;
    }

    GLuint program = Video::CreateShaderProgram_f(vertexShader, fragShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    if (program == 0) {
        std::cerr << "Shader program creation failed!" << std::endl;
        return -1;
    }

    // Load texture and bind it to the shader program
    Texture_t texture("./files/text.png", program);

    // Create a rectangle shape and pass it the texture
    Shapes::Shape_t rectangle = Shapes::Rectangle_S(0.5f, 0.9f, program, &texture);

    // Set the OpenGL viewport size
    glViewport(0, 0, 1280, 720);

    // Check for OpenGL errors after viewport setup
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
        return -1;
    }

    // Create transformation matrices
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // Move camera back
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f); // Perspective projection

    // Get the uniform locations of the transformation matrices in the shader program
    GLint modelLoc = glGetUniformLocation(program, "model");
    GLint viewLoc = glGetUniformLocation(program, "view");
    GLint projectionLoc = glGetUniformLocation(program, "projection");

    // Rotation angle for the spinning effect
    float rotationAngle = 0.0f;

    // Main rendering loop
    while (engine->GetState_f()) {
        engine->Capture_f(); // Capture user input or events
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        glUseProgram(program); // Use the shader program

        // Rotate the model matrix every frame to make it spin
        rotationAngle++;

        // Apply rotation around the Y-axis
        model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

        // Pass the transformation matrices to the shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the rectangle
        rectangle.Draw();

        engine->Refresh_f(); // Refresh the window
    }

    // Clean up OpenGL resources before exit
    glDeleteProgram(program);

    return 0;
}
