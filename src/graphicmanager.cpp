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

// Set up vertex data (and buffer(s)) and attribute pointers
// Cube vertices
// This is used for show the perspective projection
const GLfloat cubeVertices[] =
{
  // Position (x, y, z)         // Normal direction (x, y, z)   // Texture Coordinates (x, y)

  // Back side - Triangle 1
  -0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            1.0f, 1.0f,
  // Back side - Triangle 2
   0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,           0.0f,  0.0f, -1.0f,            0.0f, 0.0f,

  // Front side - Triangle 1
  -0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            1.0f, 1.0f,
  // Front side - Triangle 2
   0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,           0.0f,  0.0f,  1.0f,            0.0f, 0.0f,

  // Left side - Triangle 1
  -0.5f,  0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,            1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,            1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,            0.0f, 1.0f,
  // Left side - Triangle 2
  -0.5f, -0.5f, -0.5f,          -1.0f,  0.0f,  0.0f,            0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,            0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,          -1.0f,  0.0f,  0.0f,            1.0f, 0.0f,

  // Right side - Triangle 1
   0.5f,  0.5f,  0.5f,           1.0f,  0.0f,  0.0f,            1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,           1.0f,  0.0f,  0.0f,            1.0f, 1.0f,
   0.5f, -0.5f, -0.5f,           1.0f,  0.0f,  0.0f,            0.0f, 1.0f,
  // Right side - Triangle 2
   0.5f, -0.5f, -0.5f,           1.0f,  0.0f,  0.0f,            0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,           1.0f,  0.0f,  0.0f,            0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,           1.0f,  0.0f,  0.0f,            1.0f, 0.0f,

  // Bottom side - Triangle 1
  -0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,            0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,            1.0f, 1.0f,
   0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,            1.0f, 0.0f,
  // Bottom side - Triangle 2
   0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,            1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,           0.0f, -1.0f,  0.0f,            0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,           0.0f, -1.0f,  0.0f,            0.0f, 1.0f,

  // Top side - Triangle 1
  -0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,            0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,            1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,            1.0f, 0.0f,
  // Top side - Triangle 2
   0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,            1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,           0.0f,  1.0f,  0.0f,            0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,           0.0f,  1.0f,  0.0f,            0.0f, 1.0f,
};

// Positions of all cubes
glm::vec3 cubePositions[] =
{
  glm::vec3( 0.0f,  0.0f,   0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f,  -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f,  -3.5f),
  glm::vec3(-1.7f,  3.0f,  -7.5f),
  glm::vec3( 1.3f, -2.0f,  -2.5f),
  glm::vec3( 1.5f,  2.0f,  -2.5f),
  glm::vec3( 1.5f,  0.2f,  -1.5f),
  glm::vec3(-1.3f,  1.0f,  -1.5f),
};
int cubesCount = 10;
GLsizei cubeVerticesCount = 36;

// Positions of the point lights
glm::vec3 pointLightPositions[] =
{
  glm::vec3( 0.7f,  0.2f,   2.0f),
  glm::vec3( 2.3f, -3.3f,  -4.0f),
  glm::vec3(-4.0f,  2.0f, -12.0f),
  glm::vec3( 0.0f,  0.0f,  -3.0f),
};
int pointLightsCount = 4;

glm::mat4 projection;

glm::vec3 lightPosition(1.2f, 1.0f, -2.0f);

GLuint diffuseMap, specularMap, emissionMap;



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  /*
  glDeleteVertexArrays(lightVAOsize, &lightVAO);
  glDeleteVertexArrays(boxVAOsize, &boxVAO);
  glDeleteBuffers(VBOsize, &VBO);
  */

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

  // OpenGL options
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
  /*
  // Build and compile our shader program

  lightingShader = GraphicShader({ std::make_pair(GL_VERTEX_SHADER, "data/shaders/graphic_lighting_vertex.shader"), std::make_pair(GL_FRAGMENT_SHADER, "data/shaders/graphic_lighting_fragment.shader") });
  lampShader = GraphicShader({ std::make_pair(GL_VERTEX_SHADER, "data/shaders/graphic_lamp_vertex.shader"), std::make_pair(GL_FRAGMENT_SHADER, "data/shaders/graphic_lamp_fragment.shader") });



  GLvoid* previousDataOffset;
  int index, dataValuesCount, verticesType, verticeDataSize;
    
  // Lighting shader

  // First, set the container's VAO and VBO

  // Generate
  glGenVertexArrays(boxVAOsize, &boxVAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind
  glBindVertexArray(boxVAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO
  
  // Set data
  // Set VAO data - Position attribute
  index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VAO data - Normal attribute
  index = 1, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(3 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VAO data - Texture attribute
  index = 2, dataValuesCount = 2, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)(6 * sizeof(GLfloat));
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset);
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // VBO

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO



  // Lamp shader

  // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))

  // Generate
  glGenVertexArrays(boxVAOsize, &lightVAO); // VAO
  glGenBuffers(VBOsize, &VBO); // VBO

  // Bind
  glBindVertexArray(lightVAO); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // VBO; We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need
  
  // Set data
  // Set VAO data - Position attribute
  index = 0, dataValuesCount = 3, verticesType = GL_FLOAT, verticeDataSize = 8 * sizeof(GLfloat);
  previousDataOffset = (GLvoid *)0;
  glVertexAttribPointer(index, dataValuesCount, verticesType, GL_FALSE, verticeDataSize, previousDataOffset); // Set the vertex attributes (only position data for the lamp)); Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions)
  glEnableVertexAttribArray(index); // VAO
  // Set VBO data
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // VBO

  // Unbind
  glBindVertexArray(0); // VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO



  // Texture

  // Generate
  glGenTextures(1, &diffuseMap);
  glGenTextures(1, &specularMap);
  glGenTextures(1, &emissionMap);

  int textureWidth, textureHeight;
  unsigned char* image;

  // Diffuse map
  image = SOIL_load_image("data/images/container2.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);
  glBindTexture(GL_TEXTURE_2D, diffuseMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  // Specular map
  image = SOIL_load_image("data/images/container2_specular.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);
  glBindTexture(GL_TEXTURE_2D, specularMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  // Unbind
  glBindTexture(GL_TEXTURE_2D, 0);



  // Set texture units
  lightingShader.useProgram();
  GLuint lightingProgram = lightingShader.getProgram();
  glUniform1i(glGetUniformLocation(lightingProgram, "material.diffuse"), 0);
  glUniform1i(glGetUniformLocation(lightingProgram, "material.specular"), 1);
  */



  // Model shader
  
  modelShader = GraphicShader({ std::make_pair(GL_VERTEX_SHADER, "data/shaders/model_vertex.shader"), std::make_pair(GL_FRAGMENT_SHADER, "data/shaders/model_fragment.shader") });

  modelObject = Model("data/models/nanosuit/nanosuit.obj");



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
  
  return true;
}

void GraphicManager::update()
{
  // Clear the colorbuffer
  glClearColor(THEME_CLEARCOLOR_R, THEME_CLEARCOLOR_G, THEME_CLEARCOLOR_B, THEME_CLEARCOLOR_A); // RGBA
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
  

  
  // Model/View matrices
  glm::mat4 model, view;



  // Perspective
  //GLfloat rotationDegrees = 0.5f;
  //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  //model = glm::rotate(model, rotationDegrees, glm::vec3(1.0f, 0.0f, 0.0f));

  // Orthographic
  //GLfloat rotationDegrees = ((GLfloat)SDL_GetTicks() / 1000.0f) * 1.0f;
  //view = glm::translate(view, glm::vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -700.0f));
  //model = glm::rotate(model, rotationDegrees, glm::vec3(0.5f, 1.0f, 0.0f));


  
  // Create camera transformations
  view = camera->getViewMatrix();

  // Projection - It here will keep the zoom working (see the other one within onInit())
  float nearClippingPlane = 0.1f; // zNear
  float farClippingPlane = 1000.0f; // zFar
  projection = glm::perspective(camera->getZoomSize(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, nearClippingPlane, farClippingPlane);



  /*
  glm::mat4 model;
  GLint modelLocation, viewLocation, projectionLocation;
  glm::vec3 diffuseColor, ambientColor;



  // Lighting position movement
  //lightPosition.x -= 0.001f;
  //lightPosition.y -= 0.001f;
  //lightPosition.z -= 0.001f;



  // Lighting shader

  // Lighting shader program
  // Use corresponding shader when setting uniforms/drawing objects to draw the object, binding the appropriate shader
  lightingShader.useProgram();

  GLuint lightingProgram = lightingShader.getProgram();

  GLint viewPositionLocation = glGetUniformLocation(lightingProgram, "viewPosition");
  glUniform3f(viewPositionLocation, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
  // Set material properties
  glUniform1f(glGetUniformLocation(lightingProgram, "material.shininess"), 32.0f);

  // Here we set all the uniforms for the 5/6 types of lights we have.
  // We have to set them manually and index the proper PointLight struct in the array to set each uniform variable.
  // This can be done more code-friendly by defining light types as classes and set their values in there,
  // or by using a more efficient uniform approach by using 'Uniform buffer objects',
  // but that is Advanced GLSL, in which will not be implemented in here.

  // Directional light
  glUniform3f(glGetUniformLocation(lightingProgram, "directionalLight.direction"), -0.2f, -1.0f, -0.3f);
  glUniform3f(glGetUniformLocation(lightingProgram, "directionalLight.ambient"), 0.05f, 0.05f, 0.05f);
  glUniform3f(glGetUniformLocation(lightingProgram, "directionalLight.diffuse"), 0.4f, 0.4f, 0.4f);
  glUniform3f(glGetUniformLocation(lightingProgram, "directionalLight.specular"), 0.5f, 0.5f, 0.5f);

  // Point light 1
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[0].constant"), 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[0].linear"), 0.09f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[0].quadratic"), 0.032f);

  // Point light 2
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[1].constant"), 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[1].linear"), 0.09f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[1].quadratic"), 0.032f);

  // Point light 3
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[2].constant"), 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[2].linear"), 0.09f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[2].quadratic"), 0.032f);

  // Point light 4
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
  glUniform3f(glGetUniformLocation(lightingProgram, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[3].constant"), 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[3].linear"), 0.09f);
  glUniform1f(glGetUniformLocation(lightingProgram, "pointLights[3].quadratic"), 0.032f);

  // SpotLight
  glUniform3f(glGetUniformLocation(lightingProgram, "spotLight.position"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
  glUniform3f(glGetUniformLocation(lightingProgram, "spotLight.direction"), camera->getFrontVector().x, camera->getFrontVector().y, camera->getFrontVector().z);
  glUniform3f(glGetUniformLocation(lightingProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
  glUniform3f(glGetUniformLocation(lightingProgram, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
  glUniform3f(glGetUniformLocation(lightingProgram, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "spotLight.constant"), 1.0f);
  glUniform1f(glGetUniformLocation(lightingProgram, "spotLight.linear"), 0.09f);
  glUniform1f(glGetUniformLocation(lightingProgram, "spotLight.quadratic"), 0.032f);
  glUniform1f(glGetUniformLocation(lightingProgram, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
  glUniform1f(glGetUniformLocation(lightingProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
  
  // Get the uniform locations
  modelLocation = glGetUniformLocation(lightingProgram, "model");
  viewLocation = glGetUniformLocation(lightingProgram, "view");
  projectionLocation = glGetUniformLocation(lightingProgram, "projection");
  // Pass the matrices to the shader
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  // Bind diffuse map
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, diffuseMap);

  // Bind specular map
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, specularMap);

  // Draw cubes with the same VAO and VBO information; only their world space coordinates differ
  glBindVertexArray(boxVAO);
  for (GLuint i = 0; i < (GLuint)cubesCount; i++)
  {
    model = glm::mat4();
    model = glm::translate(model, cubePositions[i]);
    GLfloat angle = 20.0f * i;
    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);
  }
  glBindVertexArray(0);



  // Lamp shader

  // Lamp shader program
  // Use corresponding shader when setting uniforms/drawing objects to draw the object, binding the appropriate shader
  lampShader.useProgram();

  GLuint lampProgram = lampShader.getProgram();

  // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
  modelLocation = glGetUniformLocation(lampProgram, "model");
  viewLocation = glGetUniformLocation(lampProgram, "view");
  projectionLocation = glGetUniformLocation(lampProgram, "projection");

  // Pass the matrices to the shader
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  // Set matrices
  model = glm::mat4();
  model = glm::translate(model, lightPosition);
  model = glm::scale(model, glm::vec3(0.2f));

  // Pass the matrix to the shader
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

  // Draw the light object (using light's vertex attributes)
  glBindVertexArray(lightVAO);
  glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);

  // Unbind
  glBindVertexArray(0);

  // Draw as many light bulbs as we have point lights
  glBindVertexArray(lightVAO);
  for (GLuint i = 0; i < (GLuint)pointLightsCount; i++)
  {
    model = glm::mat4();
    model = glm::translate(model, pointLightPositions[i]);
    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, cubeVerticesCount);
  }
  glBindVertexArray(0);
  */



  // Model shader

  // Lighting shader program
  // Use corresponding shader when setting uniforms/drawing objects to draw the object, binding the appropriate shader
  modelShader.useProgram();

  GLuint modelProgram = modelShader.getProgram();

  glUniformMatrix4fv(glGetUniformLocation(modelProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(modelProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

  // Draw the loaded model
  model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
  model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // It's a bit too big for our scene, so scale it down
  glUniformMatrix4fv(glGetUniformLocation(modelProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  modelObject.draw(modelShader);
}
