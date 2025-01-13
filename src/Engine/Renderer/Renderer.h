#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../Error/Error.h"
#include "../Window/Window.h"

namespace Hjalmari7 {
    class Renderer {
    public:
        Renderer(WindowFrame_t* frame);
        ~Renderer();

        // Getters
        Error_t GetError_f() const;

        // Rendering functions
        void BeginRender_f();
        void Update_f();

    private:
        bool SetupOpenGLAttributes();
        void InitializeOpenGLDefaults();
        Error_t CreateContext_f();

        struct RendererHeader_t {
            SDL_GLContext OpenGL;  // OpenGL context
        };

        RendererHeader_t Header;
        SDL_Window* window;  // Window handle
        Error_t err;         // Error state
    };
}

#endif // RENDERER_H
