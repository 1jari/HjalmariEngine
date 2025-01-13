#ifndef _ENGINE_H
#define _ENGINE_H
#define SDL2_MAIN_HANDLED
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "./Error/Error.h"
#include "./Renderer/Renderer.h"
#include "./Window/Window.h"

#define ENGINE_NO_FLAGS 0x00000000

namespace Hjalmari7 { 

    class Engine {
    public:
        // Constructor with default values for position
        Engine(const std::string& title, int width, int height);
        ~Engine();

        // Get Running State
        bool        GetState_f(); 
        void        Capture_f();
        void        Refresh_f();
        // Get Last error
        bool    TraceErrors_f(); 
        float   GetTime_f();

        // Get Error Stack
        std::vector<Error_t>    GetErrors_f() const;

    private: 
        // Runtime things
        typedef struct Runtime_t {
            std::vector<Error_t>    errorStack;
            Error_t                 err;     
            bool                    isRunning;
            SDL_Event               event;
            Uint32 startTime;
            int frameCount;
            int fps;
            float timeElapsed;
        };  

        Window*         window;
        Runtime_t       Runtime;
        Renderer*       renderer;
    };
}

#endif //_ENGINE_H
