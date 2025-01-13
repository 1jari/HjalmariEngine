#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <GL/gl.h> 
#define     DEFAULT_VERTEX_SHADER_SRC R"(#version 330 core in vec2 vertex;void main(){gl_Position=vec4(vertex, 0.0, 1.0);})"
#define     DEFAULT_FRAG_SHADER_SRC R"(#version 330 core out vec4 color;void main(){color=vec4(1.0f, 0.5f, 0.2f, 1.0);})"
#define     DEFAULT_VERTEX_SHADER   (Hjalmari7::Video::CompileShader_f(DEFAULT_VERTEX_SHADER_SRC, GL_VERTEX_SHADER))
#define     DEFAULT_FRAG_SHADER     (Hjalmari7::Video::CompileShader_f(DEFAULT_FRAG_SHADER_SRC, GL_FRAGMENT_SHADER))
#define     DEFAULT_SHADER_PROGRAM  (Hjalmari7::Video::CreateShaderProgram_f(DEFAULT_VERTEX_SHADER, DEFAULT_FRAG_SHADER))


namespace Hjalmari7 { 
    namespace Video {   
        
        GLuint CompileShader_f(const char* src, GLenum kind) ;
        GLuint CreateShaderProgram_f(GLuint vertexShader, GLuint fragmentShader) ;
        GLuint GenerateVertexObjects_f( const std::vector<float>& vertices, 
                                        const std::vector<GLuint>& indices, 
                                        const std::vector<int>& attributeSizes); 
    }
}

#endif //_SHADER_H