#include "Engine.h"

namespace Hjalmari7 {

    Engine::Engine(const std::string& title, int width, int height) {
        // Initialize the runtime state 
        Runtime.err         = ERROR_OK; 
        Runtime.isRunning   = false;

        // Create the window and renderer with smart pointers
        this->window    = new Window(title, width, height);
        this->renderer  = new Renderer(&window->GetFrame());

        // Check for errors during window creation
        Runtime.err = window->GetErr_f();
        if (!TraceErrors_f()) {
            Runtime.isRunning = true;  // Start the engine if no critical errors
        }

        Runtime.startTime   = SDL_GetTicks64();
        Runtime.frameCount  = 0;
        Runtime.fps         = 0;
    }

    Engine::~Engine() {
        // Smart pointers automatically clean up resources, so no manual cleanup is needed
    }

    bool Engine::TraceErrors_f() {
        if (Runtime.err.msg != ERROR_OK.msg) {
            Runtime.errorStack.push_back(Runtime.err);

            // Handle fatal errors (e.g., ERROR_GRAVITY_JUPITER)
            if (Runtime.err.gravity == ERROR_GRAVITY_JUPITER) {
                std::cerr << "Fatal error occurred: " << Runtime.err.msg << std::endl;
                Runtime.isRunning = false;
                return true;
            }

            // Reset the error state for non-fatal errors
            Runtime.err = ERROR_OK;
        }
        return false;
    }

    std::vector<Error_t> Engine::GetErrors_f() const {
        return Runtime.errorStack;
    }

    bool Engine::GetState_f() {
        return Runtime.isRunning;
    }

    void Engine::Capture_f() {
        renderer->BeginRender_f();

        // Handle events
        while (SDL_PollEvent(&Runtime.event)) {
            if (Runtime.event.type == SDL_WINDOWEVENT &&
                Runtime.event.window.event == SDL_WINDOWEVENT_CLOSE) {
                Runtime.isRunning = false;
            }
        }
    }

    float Engine::GetTime_f() {
        return Runtime.timeElapsed;
    }

    void Engine::Refresh_f() {
        renderer->Update_f();
        
        Runtime.frameCount++;

        // Calculate FPS and elapsed time every second
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - Runtime.startTime >= 1000) {
            Runtime.fps = Runtime.frameCount;           // Store the FPS
            Runtime.timeElapsed = (currentTime - Runtime.startTime) / 1000.0f; // Time in seconds
            std::cout << "FPS: " << Runtime.fps << ", Time Elapsed: " << Runtime.timeElapsed << " seconds" << std::endl;

            Runtime.frameCount = 0;   // Reset the frame count
            Runtime.startTime = currentTime;  // Reset the start time
        }

        // Optional: Limit the frame rate based on actual time
        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < 16) {  // If the frame took less than 16ms (~60 FPS)
            SDL_Delay(16 - frameTime);  // Add a small delay to maintain 60 FPS
        }
    }
}