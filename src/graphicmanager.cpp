/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



// VBO - Vertex Buffer Object, VAO - Vertex Array Object, Texture
GLuint VBO, VAO, texture;
GLsizei VBOsize = 1, VAOsize = 1, textureSize = 1;

// Cube vertices
// This is used for show the perspective projection
const GLfloat cubeVertices[] =
{
  // Position (x, y, z)         // Texture Coordinates (x, y)

  // Back side - Triangle 1
  -0.5f, -0.5f, -0.5f,          0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,          1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,          1.0f, 1.0f,
  // Back side - Triangle 2
   0.5f,  0.5f, -0.5f,          1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,          0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,          0.0f, 0.0f,

  // Front side - Triangle 1
  -0.5f, -0.5f,  0.5f,          0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,          1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,          1.0f, 1.0f,
  // Front side - Triangle 2
   0.5f,  0.5f,  0.5f,          1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,          0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,          0.0f, 0.0f,

  // Left side - Triangle 1
  -0.5f,  0.5f,  0.5f,          1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,          1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,          0.0f, 1.0f,
  // Left side - Triangle 2
  -0.5f, -0.5f, -0.5f,          0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,          0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,          1.0f, 0.0f,

  // Right side - Triangle 1
   0.5f,  0.5f,  0.5f,          1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,          1.0f, 1.0f,
   0.5f, -0.5f, -0.5f,          0.0f, 1.0f,
  // Right side - Triangle 2
   0.5f, -0.5f, -0.5f,          0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,          0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,          1.0f, 0.0f,

  // Bottom side - Triangle 1
  -0.5f, -0.5f, -0.5f,          0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,          1.0f, 1.0f,
   0.5f, -0.5f,  0.5f,          1.0f, 0.0f,
  // Bottom side - Triangle 2
   0.5f, -0.5f,  0.5f,          1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,          0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,          0.0f, 1.0f,

  // Top side - Triangle 1
  -0.5f,  0.5f, -0.5f,          0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,          1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,          1.0f, 0.0f,
  // Top side - Triangle 2
   0.5f,  0.5f,  0.5f,          1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,          0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,          0.0f, 1.0f,
};

const int cubesCount = 10;
glm::vec3 cubePositions[cubesCount];

glm::mat4 projection;



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  glDeleteVertexArrays(VAOsize, &VAO);
  glDeleteBuffers(VBOsize, &VBO);
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

  // Depth
  glEnable(GL_DEPTH_TEST);

  // Blend
  glEnable(GL_BLEND); // Images can now be blended
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha support
  
  // Camera
  camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));

  // onInit
  if (!onInit())
    return false;
  
  initialized = true;
  return initialized;
}

bool GraphicManager::onInit()
{
  cubePositions[0] = glm::vec3( 0.0f,  0.0f,   0.0f);
  cubePositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
  cubePositions[2] = glm::vec3(-1.5f, -2.2f,  -2.5f);
  cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
  cubePositions[4] = glm::vec3( 2.4f, -0.4f,  -3.5f);
  cubePositions[5] = glm::vec3(-1.7f,  3.0f,  -7.5f);
  cubePositions[6] = glm::vec3( 1.3f, -2.0f,  -2.5f);
  cubePositions[7] = glm::vec3( 1.5f,  2.0f,  -2.5f);
  cubePositions[8] = glm::vec3( 1.5f,  0.2f,  -1.5f);
  cubePositions[9] = glm::vec3(-1.3f,  1.0f,  -1.5f);

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
  glGenTextures(textureSize, &texture); // Texture



  // Bind
  glBindVertexArray(VAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  glBindTexture(GL_TEXTURE_2D, texture); // Texture
  


  // Set data
  GLvoid* previousDataOffset;
  // Set VAO data - Position attribute
  int index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 5 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VAO data - Texture coordinate attribute
  index = 1, dataValuesCount = 2, verticesType = GL_FLOAT, verticeDataSize = 5 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(3 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // VBO
  // Set texture data (see wrapping techniques)
  int width, height;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char *image = SOIL_load_image("data/link_shield.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO
  glBindTexture(GL_TEXTURE_2D, 0); // Texture
  SOIL_free_image_data(image); // Texture

  // See https://www.oreilly.com/library/view/learn-opengl/9781789340365/assets/1fb8ca0b-0f34-4afa-bccb-b183108d6da2.png
  // See (left is perspective, right is orthographic) http://www.songho.ca/opengl/files/gl_projectionmatrix01.png
  //float viewDegrees = 45.0f; // Angle from x axis to Up vector
  //float nearClippingPlane = 0.1f; // zNear
  //float farClippingPlane = 1000.0f; // zFar
  //projection = glm::perspective(viewDegrees, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);
  //projection = glm::ortho(0.0f, (GLfloat)SCREEN_WIDTH, 0.0f, (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);

  return true;
}

void GraphicManager::update()
{
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers



  // Apply texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(graphicShader.getProgram(), "graphicTexture"), 0);



  // Shader program
  graphicShader.useProgram();


  
  // Model/View matrices
  //glm::mat4 model, view;

  // Perspective
  //GLfloat rotationDegrees = 0.5f;
  //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  //model = glm::rotate(model, rotationDegrees, glm::vec3(1.0f, 0.0f, 0.0f));

  // Orthographic
  //GLfloat rotationDegrees = ((GLfloat)SDL_GetTicks() / 1000.0f) * 1.0f;
  //view = glm::translate(view, glm::vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -700.0f));
  //model = glm::rotate(model, rotationDegrees, glm::vec3(0.5f, 1.0f, 0.0f));



  // Camera projection
  glm::mat4 view = camera->getViewMatrix();

  float nearClippingPlane = 0.1f; // zNear
  float farClippingPlane = 1000.0f; // zFar
  projection = glm::perspective(camera->getZoomSize(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);

  GLint modelLocation = glGetUniformLocation(graphicShader.getProgram(), "model");
  GLint viewLocation = glGetUniformLocation(graphicShader.getProgram(), "view");
  GLint projectionLocation = glGetUniformLocation(graphicShader.getProgram(), "projection");
  //glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));



  // Draw object map
  // Bind
  glBindVertexArray(VAO); // VAO
  // Draw
  for (GLuint i = 0; i < cubesCount; i++)
  {
    glm::mat4 _model;
    _model = glm::translate(_model, cubePositions[i]);
    GLfloat angle = 20.0f * i;
    _model = glm::rotate(_model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_model));

    int verticesCount = 36;
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
  }
  // Unbind
  glBindVertexArray(0); // VAO
}
