/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



// VBO - Vertex Buffer Object, VAO - Vertex Array Object
GLuint VBO, boxVAO, lightVAO;
GLsizei VBOsize = 1, boxVAOsize = 1, lightVAOsize;

// Cube vertices
// This is used for show the perspective projection
const GLfloat cubeVertices[] =
{
  // Position (x, y, z)         // Normal direction (x, y, z)

  // Back side - Triangle 1
  -0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,
   0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,
  // Back side - Triangle 2
   0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,

  // Front side - Triangle 1
  -0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,
   0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,
  // Front side - Triangle 2
   0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,

  // Left side - Triangle 1
  -0.5f,  0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,
  // Left side - Triangle 2
  -0.5f, -0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,

  // Right side - Triangle 1
   0.5f,  0.5f,  0.5f,           1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f,           1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f,           1.0f,  0.0f,  0.0f,
  // Right side - Triangle 2
   0.5f, -0.5f, -0.5f,           1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f,           1.0f,  0.0f,  0.0f,
   0.5f,  0.5f,  0.5f,           1.0f,  0.0f,  0.0f,

  // Bottom side - Triangle 1
  -0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,
   0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,
  // Bottom side - Triangle 2
   0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,

  // Top side - Triangle 1
  -0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,
   0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,
  // Top side - Triangle 2
   0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,
};

glm::mat4 projection;

glm::vec3 lightPosition;



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  glDeleteVertexArrays(lightVAOsize, &lightVAO);
  glDeleteVertexArrays(boxVAOsize, &boxVAO);
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

  // Depth
  glEnable(GL_DEPTH_TEST);

  // Blend
  glEnable(GL_BLEND); // Images can now be blended
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha support
  
  // Camera
  camera = new Camera();
  camera->updateCamera(DEFAULT_CAMERA, DEFAULT_CAMERA_DISTANCE);

  // onInit
  if (!onInit())
    return false;
  
  initialized = true;
  return initialized;
}

bool GraphicManager::onInit()
{
  // Load graphic shader
  lightingShader = GraphicShader();
  // Lighting vertex shader
  GLuint lightingVertex = lightingShader.loadShader(GL_VERTEX_SHADER, "data/shaders/graphic_lighting_vertex.shader");
  if (lightingVertex == 0)
    return false;
  // Lighting fragment shader
  GLuint lightingFragment = lightingShader.loadShader(GL_FRAGMENT_SHADER, "data/shaders/graphic_lighting_fragment.shader");
  if (lightingFragment == 0)
    return false;
  // Load program
  lightingShader.loadProgram();
  // Attach shaders
  lightingShader.attachShader(lightingVertex);
  lightingShader.attachShader(lightingFragment);
  // Shader program
  if (!lightingShader.linkProgram())
    return false;

  // Load graphic shader
  lampShader = GraphicShader();
  // Lamp vertex shader
  GLuint lampVertex = lampShader.loadShader(GL_VERTEX_SHADER, "data/shaders/graphic_lamp_vertex.shader");
  if (lampVertex == 0)
    return false;
  // Lamp fragment shader
  GLuint lampFragment = lampShader.loadShader(GL_FRAGMENT_SHADER, "data/shaders/graphic_lamp_fragment.shader");
  if (lampFragment == 0)
    return false;
  // Load program
  lampShader.loadProgram();
  // Attach shaders
  lampShader.attachShader(lampVertex);
  lampShader.attachShader(lampFragment);
  // Shader program
  if (!lampShader.linkProgram())
    return false;



  GLvoid* previousDataOffset;
  int index, dataValuesCount, verticesType, verticeDataSize;


  
  // Generate
  glGenVertexArrays(boxVAOsize, &boxVAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind
  glBindVertexArray(boxVAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  
  // Set data
  // Set VAO data - Position attribute
  index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 6 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // VBO
  // Set VAO data - Normal attribute
  index = 1, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 6 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(3 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO



  // Generate
  glGenVertexArrays(boxVAOsize, &lightVAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind
  glBindVertexArray(lightVAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  
  // Set data
  // Set VAO data - Position attribute
  index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 6 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // VBO

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO



  // See https://www.oreilly.com/library/view/learn-opengl/9781789340365/assets/1fb8ca0b-0f34-4afa-bccb-b183108d6da2.png
  // See (left is perspective, right is orthographic) http://www.songho.ca/opengl/files/gl_projectionmatrix01.png
  //float viewDegrees = 45.0f; // Angle from x axis to Up vector
  //float nearClippingPlane = 0.1f; // zNear
  //float farClippingPlane = 1000.0f; // zFar
  //projection = glm::perspective(viewDegrees, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);
  //projection = glm::ortho(0.0f, (GLfloat)SCREEN_WIDTH, 0.0f, (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);

  // Projection - It here will make the zoom not work anymore (see the other one within update())
  //float nearClippingPlane = 0.1f; // zNear
  //float farClippingPlane = 1000.0f; // zFar
  //projection = glm::perspective(camera->getZoomSize(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);

  // Light
  lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

  return true;
}

void GraphicManager::update()
{
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
  

  
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



  GLsizei cubeVerticesCount = 36;
  glm::mat4 model, view;
  view = camera->getViewMatrix();
  GLint modelLocation, viewLocation, projectionLocation;

  // Projection - It here will keep the zoom working (see the other one within onInit())
  float nearClippingPlane = 0.1f; // zNear
  float farClippingPlane = 1000.0f; // zFar
  projection = glm::perspective(camera->getZoomSize(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);



  // Lighting position movement
  lightPosition.x -= 0.001f;
  //lightPosition.y -= 0.001f;
  lightPosition.z -= 0.001f;



  // Lighting shader program
  lightingShader.useProgram();

  GLuint lightingProgram = lightingShader.getProgram();

  GLint objectColorLocation = glGetUniformLocation(lightingProgram, "objectColor");
  GLint lightColorLocation = glGetUniformLocation(lightingProgram, "lightColor");
  GLint lightPositionLocation = glGetUniformLocation(lightingProgram, "lightPosition");
  GLint viewPositionLocation = glGetUniformLocation(lightingProgram, "viewPosition");
  glUniform3f(objectColorLocation, 1.0f, 0.5f, 0.31f);
  glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
  glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
  glUniform3f(viewPositionLocation, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

  modelLocation = glGetUniformLocation(lightingProgram, "model");
  viewLocation = glGetUniformLocation(lightingProgram, "view");
  projectionLocation = glGetUniformLocation(lightingProgram, "projection");

  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  glBindVertexArray(boxVAO);
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);
  glBindVertexArray(0);



  // Lamp shader program
  lampShader.useProgram();

  GLuint lampProgram = lampShader.getProgram();

  modelLocation = glGetUniformLocation(lampProgram, "model");
  viewLocation = glGetUniformLocation(lampProgram, "view");
  projectionLocation = glGetUniformLocation(lampProgram, "projection");

  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
  
  model = glm::mat4();
  model = glm::translate(model, lightPosition);
  model = glm::scale(model, glm::vec3(0.2f));
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

  glBindVertexArray(lightVAO);
  glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);
  glBindVertexArray(0);
}
