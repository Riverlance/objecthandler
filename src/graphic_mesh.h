/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <GL/glew.h>
#include "graphic_shader.h"
#include "const.h"



class Mesh
{
  public:
    Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures);



    // Render the mesh
    void draw(GraphicShader graphicShader);


    
    std::vector<Vertex> getVertices() { return vertices; }
    std::vector<GLuint> getIndices() { return indices; }
    std::vector<Texture> getTextures() { return textures; }



  private:
    // Mesh Data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    // Render data
    GLuint VAO, VBO, EBO;



    // Initializes all the buffer objects/arrays
    void setupMesh();
};
