/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphicmanager.h"



GraphicManager::GraphicManager()
{
  initialized = false;
  viewportX = 0;
  viewportY = 0;
  viewportWidth = 0;
  viewportHeight = 0;
}

GraphicManager::~GraphicManager()
{
  // Since is a Singleton class, we should clear all vars because this object is never deleted
  initialized = false;
}



bool GraphicManager::init()
{
  std::cout << std::endl;

  if (glewInit() == GLEW_OK)
    std::cout << "> OpenGL initialized successfully." << std::endl;
  else
  {
    std::cout << "> Failed to initialize GLEW." << std::endl;
    return false;
  }

  std::cout << "\tOpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Set viewport dimensions
  glViewport(viewportX, viewportY, viewportWidth, viewportHeight);



  initialized = true;
  return initialized;
}
