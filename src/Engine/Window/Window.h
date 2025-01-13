#ifndef _Window_H
#define _Window_H

#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "../Error/Error.h" 

namespace Hjalmari7 {

    typedef struct WindowFrame_t {
        glm::vec2   size;
        glm::vec2   pos;
        std::string title; 
        SDL_Window* window;
    }; 

    class Window {
    public:
        // Constructor with default values for position
        Window(std::string title, int width, int height); 
        ~Window(); 
        WindowFrame_t   GetFrame();
        Error_t         GetErr_f() const;  
    private: 
        // Function to initialize and process the window
        Error_t         WindowProcedure_f(); 
        Error_t         err;
        // Members for window and runtime properties
        WindowFrame_t   Frame; 
        bool            isInitialized; // Track SDL initialization
    };
}

#endif //_Window_H
