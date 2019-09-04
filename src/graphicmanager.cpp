/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



// VBO - Vertex Buffer Object, VAO - Vertex Array Object, EBO - Element Buffer Object, Texture
GLuint VBO, VAO, EBO, texture;
GLsizei VBOsize = 1, VAOsize = 1, EBOsize = 1, textureSize = 1;

// Rectangle vertices
const GLfloat rectangleVertices[] =
{
  // Position (x, y, z)     // Color (r, g, b)    // Texture Coordinates (x, y)
  -0.5f, -0.5f, 0.0f,       1.0f, 0.0f, 0.0f,     0.0f, 0.0f,                     // Bottom Left
  0.5f, -0.5f, 0.0f,        1.0f, 1.0f, 1.0f,     1.0f, 0.0f,                     // Bottom Right
  -0.5f, 0.5f, 0.0f,        1.0f, 0.0f, 1.0f,     0.0f, 1.0f,                     // Top Left
  0.5f, 0.5f, 0.0f,         1.0f, 0.0f, 0.0f,     1.0f, 1.0f,                     // Top Right
};

const GLuint rectangleIndices[] = // Based on rectangleVertices
{
  // See: http://www.opengl-tutorial.org/assets/images/tuto-9-vbo-indexing/indexing1.png

  // Without indexes
  0, 1, 2, // Point indexes of south-west triangle (bottom left, bottom right, top left)
  1, 2, 3, // Point indexes of north-east triangle (bottom right, top left, top right)

  // With indexes
  //0, 1, 2, // Point indexes of south-west triangle (bottom left, bottom right, top left)
  //3, // Point indexes of north-east triangle (bottom right, bottom left, top left) - Here has only one since 1, 2 (that is part of this triangle) were mentioned already
};



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  glDeleteVertexArrays(VAOsize, &VAO);
  glDeleteBuffers(VBOsize, &VBO);
  glDeleteBuffers(EBOsize, &EBO);
  glDeleteTextures(textureSize, &texture);

  // Since is a Singleton class, we should clear all vars because this object is never deleted
  initialized = false;
}



bool GraphicManager::init()
{
  std::cout << std::endl;

  // Modern approach to retrieving OpenGL functions pointers and extensions (not fully tested)
  glewExperimental = GL_TRUE;

  // Initiliaze GLEW to setup the OpenGL function pointers
  const GLenum glInitReturn = glewInit();
  if (glInitReturn == GLEW_OK)
    std::cout << "> OpenGL initialized successfully." << std::endl;
  else
  {
    std::cerr << "> Failed to initialize OpenGL.\n\tOpenGL Error: " << glewGetErrorString(glInitReturn) << std::endl;
    return false;
  }

  std::cout << "\tOpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Define the viewport dimensions
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  // Blend
  glEnable(GL_BLEND); // Images can now be blended
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha support

  // onInit
  if (!onInit())
    return false;
  
  initialized = true;
  return initialized;
}

bool GraphicManager::onInit()
{
  // Load graphic shader
  graphicShader = GraphicShader();

  // Vertex shader
  GLuint vertex = graphicShader.loadShader(GL_VERTEX_SHADER, "data/shaders/graphic_core_vertex.shader");
  if (vertex == 0)
    return false;
  // Fragment shader
  GLuint fragment = graphicShader.loadShader(GL_FRAGMENT_SHADER, "data/shaders/graphic_core_fragment.shader");
  if (fragment == 0)
    return false;
  
  // Load program
  graphicShader.loadProgram();
  
  // Attach shaders
  graphicShader.attachShader(vertex);
  graphicShader.attachShader(fragment);
  
  // Shader program
  if (!graphicShader.linkProgram())
    return false;


  
  // Generate
  glGenVertexArrays(VAOsize, &VAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO
  glGenBuffers(EBOsize, &EBO); // EBO
  glGenTextures(textureSize, &texture); // Texture



  // Bind
  glBindVertexArray(VAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // EBO
  glBindTexture(GL_TEXTURE_2D, texture); // Texture
  


  // Set data
  GLvoid* previousDataOffset;
  // Set VAO data - Position attribute
  int index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VAO data - Color attribute
  index = 1, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(3 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VAO data - Texture coordinate attribute
  index = 2, dataValuesCount = 2, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(6 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW); // VBO
  // Set EBO data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW); // VBO
  // Set texture data (see wrapping techniques)
  int width, height;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char *image = SOIL_load_image("data/link_shield.png", &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // EBO
  glBindTexture(GL_TEXTURE_2D, 0); // Texture
  SOIL_free_image_data(image); // Texture

  return true;
}

void GraphicManager::update()
{
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT);



  // Shader program
  graphicShader.useProgram();



  // Create transformation
  glm::mat4 transform;
  transform = glm::translate(transform, glm::vec3(-0.25f, 0.25f, 1.0f)); // Move a little to north-west
  transform = glm::rotate(transform, ((GLfloat)SDL_GetTicks() / 1000.0f) * -5.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z axis
  // std::cout << glm::to_string(transform) << std::endl << std::endl;

  // Apply transformation
  GLint transformLocation = glGetUniformLocation(graphicShader.getProgram(), "transform");
  glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

  // Apply texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(graphicShader.getProgram(), "graphicTexture"), 0);



  // Bind
  glBindVertexArray(VAO); // VAO

  // Draw triangle
  int verticesCount = 6;
  //glDrawArrays(GL_TRIANGLES, beginIndex, verticesCount); // Single triangle (beginIndex is the id of triangle)
  glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, (void*)0); // All triangles

  // Unbind
  glBindVertexArray(0); // VAO
}
