#ifndef WEBASSEMBLYDEMO_OPENGL_H
#define WEBASSEMBLYDEMO_OPENGL_H

#include "Linmath.hpp"

#include <emscripten.h>

#define GLFW_INCLUDE_ES3

#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vertex.hpp"


class OpenGL {

  public:
    OpenGL();

    ~OpenGL();

    void outputError(int error, const char* msg);

    static void generateFrame();

    int checkCompiled(GLuint shader);

    int checkLinked(GLuint program);


  private:
    static GLFWwindow* _window;
    static GLuint _vertexBuffer, _vertexShader, _fragmentShader, _program;
    static GLint _mvpLocation, _vposLocation, _vcolLocation;
    Vertex _vertices[3];
    static const char* _vertexShaderText;
    static const char* _fragmentShaderText;


};


#endif //WEBASSEMBLYDEMO_OPENGL_H
