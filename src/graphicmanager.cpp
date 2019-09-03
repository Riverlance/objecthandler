/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



// VBO - Vertex Buffer Objects, VAO - Vertex Array Object
GLuint VBO, VAO;
GLsizei VBOsize = 1, VAOsize = 1;

// Triangle vertices
const GLfloat triangleVertices[] =
{
  // pos.x, pos.y, pos.z    // color.r, color.g, color.b
  0.0f, 0.5f, 0.0f,         1.0f, 0.0f, 0.0f, // North vertice, horizontally centered
  -0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f, // South-west vertice
  0.5f, -0.5f, 0.0f,        0.0f, 0.0f, 1.0f, // South-east vertice
};



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  glDeleteVertexArrays(VAOsize, &VAO);
  glDeleteBuffers(VBOsize, &VBO);

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


  
  // Generate VAO, VBO
  glGenVertexArrays(VAOsize, &VAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind VAO, VBO
  glBindVertexArray(VAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); // VBO
  // Set VAO data
  GLvoid* previousDataOffset;
  // Position attribute
  int index = 0, verticesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 6 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, verticesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset); // Vertices
  glEnableVertexAttribArray(0); // VAO
  // Color attribute
  index = 1, verticesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 6 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(3 * sizeof(GLfloat));
  glVertexAttribPointer(index, verticesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset); // Vertices
  glEnableVertexAttribArray(1); // VAO

  // Unbind
  //glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
  glBindVertexArray(0); // VAO

  return true;
}

void GraphicManager::update()
{
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT);



  // Shader program
  graphicShader.useProgram();

  // Bind
  glBindVertexArray(VAO); // VAO

  // Draw triangle
  int beginIndex = 0, verticesCount = 3;
  glDrawArrays(GL_TRIANGLES, beginIndex, verticesCount);

  // Unbind
  glBindVertexArray(0); // VAO
}
