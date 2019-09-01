/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



 // Shader for handle position
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

// Shader for handle color
const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"  color = vec4(0.0f, 0.5f, 0.7f, 1.0f);\n"
"}";

GLuint shaderProgram;

// VBO - Vertex Buffer Objects, VAO - Vertex Array Object
GLuint VBO, VAO;
GLsizei VBOsize = 1, VAOsize = 1;

// Triangle vertices
const GLfloat triangleVertices[] =
{
  -0.5f, -0.5f, 0.0f, // South-west
  0.5f, -0.5f, 0.0f, // South-east
  0.0f, 0.5f, 0.0f, // North, horizontally centered
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
    std::cout << "> Failed to initialize OpenGL.\n\tOpenGL Error: " << glewGetErrorString(glInitReturn) << std::endl;
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
  GLint success = false;
  const int infoLogSize = 512;
  GLchar infoLog[infoLogSize];

  // Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to load vertex shader.\n" << infoLog << std::endl;
    return false;
  }

  success = false; // Reset variable

  // Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to load fragment shader.\n" << infoLog << std::endl;
    return false;
  }

  success = false; // Reset variable

  // Shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to link shader program.\n" << infoLog << std::endl;
  }

  // Shaders were used on shader program, so we can delete the shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);



  // Generate VAO, VBO
  glGenVertexArrays(VAOsize, &VAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind VAO, VBO
  glBindVertexArray(VAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO

  // Set VAO, VBO data
  glEnableVertexAttribArray(0); // VAO
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); // VBO
  int beginIndex = 0, verticesCount = 3, verticesFormat = GL_FLOAT;
  glVertexAttribPointer(beginIndex, verticesCount, verticesFormat, GL_FALSE, verticesCount * sizeof(GLfloat), (GLvoid *)0); // Vertices

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
  glBindVertexArray(0); // VAO

  return true;
}

void GraphicManager::update()
{
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT);



  // Shader program
  glUseProgram(shaderProgram);

  // Bind
  glBindVertexArray(VAO); // VAO

  // Draw triangle
  int beginIndex = 0, verticesCount = 3;
  glDrawArrays(GL_TRIANGLES, beginIndex, verticesCount);

  // Unbind
  glBindVertexArray(0); // VAO
}
