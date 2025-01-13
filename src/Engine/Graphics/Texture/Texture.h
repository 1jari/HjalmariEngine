#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <memory> 
#include <SOIL/SOIL.h>
#define LODEPNG_CPP 

namespace Hjalmari7 {
    
class Texture_t {
public:
    GLuint ID;
    int width, height, channels;
    GLint textureLoc;

    Texture_t(const std::string& filepath, GLuint program); 
    ~Texture_t(); 
    void bind() const;
};

}

#endif //_TEXTURE_H
