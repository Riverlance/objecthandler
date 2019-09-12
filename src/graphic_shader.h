/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <GL/glew.h>



class GraphicShader
{
  public:
    GraphicShader() {};
    GraphicShader(std::vector<std::pair<GLenum, const GLchar*>> shaders);



    // Generate the shader on the fly

    GLuint loadShader(GLenum shaderType, const GLchar* path);
    void loadProgram();
    bool attachShader(GLuint shader);
    bool linkProgram();



    // Use the current shader
    void useProgram();



    GLuint getProgram() { return program; }



  private:
    GLuint program;
};
