#include "Renderer.h"

namespace Hjalmari7 {

    Renderer::Renderer(WindowFrame_t* frame) 
        : window(frame->window), err(ERROR_OK) {
        // Set OpenGL attributes
        if (!SetupOpenGLAttributes()) {
            return; // If attributes fail, error is already set
        }

        // Create OpenGL context
        Header.OpenGL = SDL_GL_CreateContext(window);
        if (!Header.OpenGL) {
            err = CreateError_f("Failed to create OpenGL context!", ERROR_GRAVITY_JUPITER);
            return;
        }

        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK) {
            err = CreateError_f("Failed to initialize GLEW!", ERROR_GRAVITY_JUPITER);
            return;
        }

        // Enable V-Sync
        if (SDL_GL_SetSwapInterval(1) < 0) {
            err = CreateError_f("Unable to set V-Sync!", ERROR_GRAVITY_MARS);
        }

        // Set default OpenGL state
        InitializeOpenGLDefaults();
    }

    Renderer::~Renderer() {
        if (Header.OpenGL) {
            SDL_GL_DeleteContext(Header.OpenGL); // Clean up OpenGL context
        }
    }

    bool Renderer::SetupOpenGLAttributes() {
        // Request OpenGL 3.3 core profile
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) != 0 ||
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) != 0 ||
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0) {
            err = CreateError_f("Failed to set OpenGL attributes!", ERROR_GRAVITY_JUPITER);
            return false;
        }
        return true;
    }

    void Renderer::InitializeOpenGLDefaults() {
        // Set up viewport
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Set clear color (RGBA)
        glClearColor(0.1f, 0.45f, 0.5f, 1.0f);

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    Error_t Renderer::GetError_f() const {
        return err;
    }

    void Renderer::BeginRender_f() {
        // Clear the screen with OpenGL calls
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Update_f() {
        // Swap the OpenGL buffers to display the rendered frame
        SDL_GL_SwapWindow(window);
    }
}
