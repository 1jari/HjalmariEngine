#include "Window.h"
#include <iostream>

namespace Hjalmari7 {

    Window::Window(std::string title, int width, int height)
        : isInitialized(false) {
        this->Frame.title = title;
        this->Frame.pos = glm::vec2(200, 200);
        this->Frame.size = glm::vec2(width, height); 
        // Create the window and check for errors
        err = WindowProcedure_f();
    }

    Window::~Window() {
        // Call SDL_Quit() only if SDL was initialized
        if (isInitialized) {
            SDL_Quit();
        }
    }

    WindowFrame_t Window::GetFrame() {
        return Frame;
    }

    Error_t Window::GetErr_f() const {
        return err;
    }

    Error_t Window::WindowProcedure_f() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Unable to initialize SDL video: " << SDL_GetError() << std::endl;
            return CreateError_f("Unable to initialize video!", ERROR_GRAVITY_JUPITER);
        }

        // Mark SDL as initialized
        isInitialized = true;

        // Create the window
        Frame.window = SDL_CreateWindow(Frame.title.c_str(),
                                        Frame.pos.x,
                                        Frame.pos.y,
                                        Frame.size.x,
                                        Frame.size.y,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        // Check for window creation failure
        if (Frame.window == nullptr) {
            std::cerr << "Unable to create window: " << SDL_GetError() << std::endl;
            return CreateError_f("Unable to create Window!", ERROR_GRAVITY_JUPITER);
        }

        // Optional: Remove long delay for production, keep it for debugging if necessary
        // SDL_Delay(10000);

        return ERROR_OK;
    }
}
