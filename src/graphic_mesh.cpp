/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_mesh.h"



Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures)
{
  vertices = _vertices;
  indices = _indices;
  textures = _textures;

  // Now that we have all the required data, set the vertex buffers and its attribute pointers.
  setupMesh();
}



// Render the mesh
void Mesh::draw(GraphicShader graphicShader)
{
  // Bind appropriate textures
  GLuint diffuseNr = 1;
  GLuint specularNr = 1;

  for (GLuint i = 0; i < textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
                                      // Retrieve texture number (the N in diffuse_textureN)
    std::stringstream ss;
    std::string id;
    std::string name = textures[i].type;

    if (name == "texture_diffuse")
      ss << diffuseNr++; // Allocate GLuint to stream
    else if (name == "texture_specular")
      ss << specularNr++; // Allocate GLuint to stream

                          // Allocate string value of stream
    id = ss.str();

    // Now set the sampler to the correct texture unit
    glUniform1i(glGetUniformLocation(graphicShader.getProgram(), (name + id).c_str()), i);
    // And finally bind the texture
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }

  // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
  glUniform1f(glGetUniformLocation(graphicShader.getProgram(), "material.shininess"), 16.0f);

  // Draw mesh
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  // Always good practice to set everything back to defaults once configured
  for (GLuint i = 0; i < textures.size(); i++)
  {
    // Set texture to be unbinded
    glActiveTexture(GL_TEXTURE0 + i);

    // Unbind
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}



void Mesh::setupMesh()
{
  // Create buffers/arrays
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  // Load data into vertex buffers
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // A great thing about structs is that their memory layout is sequential for all its items.
  // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
  // again translates to 3/2 floats which translates to a byte array.
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

  // Set the vertex attribute pointers
  // Vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
  // Vertex Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
  // Vertex Texture Coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TextureCoordinates));

  glBindVertexArray(0);
}
