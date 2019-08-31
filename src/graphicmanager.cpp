/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"
#include "const.h"



GraphicManager::GraphicManager()
{
  initialized = false;
}

GraphicManager::~GraphicManager()
{
  // Since is a Singleton class, we should clear all vars because this object is never deleted
  initialized = false;
}



bool GraphicManager::init()
{
  std::cout << std::endl;

  // Create OpenGL context
  const GLenum glInitReturn = glewInit();
  if (glInitReturn == GLEW_OK)
    std::cout << "> OpenGL initialized successfully." << std::endl;
  else
  {
    std::cout << "> Failed to initialize OpenGL.\n\tOpenGL Error: " << glewGetErrorString(glInitReturn) << std::endl;
    return false;
  }

  // Modern OpenGL experimental functions
  //glewExperimental = GL_TRUE;

  std::cout << "\tOpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Set viewport dimensions
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  
  initialized = true;
  return initialized;
}

void GraphicManager::update()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // RGBA
  glClear(GL_COLOR_BUFFER_BIT);
}
