/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

//#define GLEW_STATIC

#include <SDL.h>
#include <GL/glew.h>
#include "camera.h"
#include "graphic_shader.h"



class GraphicManager
{
  public:
    // Initialize
    GraphicManager();

    // Deallocate memory
    ~GraphicManager();

    // Prevent clone this object
    GraphicManager(const GraphicManager&) = delete; // Prevent construction by copying
    GraphicManager& operator=(const GraphicManager&) = delete; // Prevent assignment



    bool init();
    bool onInit();
    void update();



    /**
      * Singleton implementation.
      *
      * @return a GLEW handler singleton
      */
    static GraphicManager* getInstance()
    {
      static GraphicManager instance;
      return &instance;
    };

    bool isInitialized() { return initialized; }

    Camera* getCamera() { return camera; }



    private:
      bool initialized;

      GraphicShader lightingShader;
      GraphicShader lampShader;

      Camera* camera;
};
