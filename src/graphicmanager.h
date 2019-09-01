/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include <GL/glew.h>



class GraphicManager
{
  public:
    // Initialize variables
    GraphicManager();

    // Deallocate memory
    ~GraphicManager();

    // Prevent clone this object
    GraphicManager(const GraphicManager&) = delete; // Prevent construction by copying
    GraphicManager& operator=(const GraphicManager&) = delete; // Prevent assignment



    bool init();
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



    private:
      bool initialized;
};

#endif
