/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef GRAPHICSHADER_H
#define GRAPHICSHADER_H

#include <GL/glew.h>



class GraphicShader
{
  public:
    GraphicShader() {};
    GraphicShader(const GLchar* vertexPath, const GLchar* fragmentPath) { load(vertexPath, fragmentPath); };

    // Generate the shader on the fly
    bool load(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Use the current shader
    void use();



    GLuint getProgram() { return program; }



  private:
    GLuint program;
};



#endif
