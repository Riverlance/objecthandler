/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef APP_H
#define APP_H

#include "windowmanager.h"
#include "graphicmanager.h"
#include "const.h"



class GApp
{
  public:
    // Initialize variables
    GApp();

    // Deallocate memory
    ~GApp();

    // Prevent clone this object
    GApp(const GApp&) = delete; // Prevent construction by copying
    GApp& operator=(const GApp&) = delete; // Prevent assignment



    bool init(int argc, char* argv[]);
    static void setTheme(Theme theme = THEME_DEFAULT);



    /**
      * Singleton implementation.
      *
      * @return a SDL window handler singleton
      */
    static GApp* getInstance()
    {
      static GApp instance;
      return &instance;
    };

    bool isInitialized() { return initialized; }
    WindowManager* getWindowManager() { return windowManager; }
    GraphicManager* getGraphicManager() { return graphicManager; }



  private:
    bool initialized;

    WindowManager* windowManager;
    GraphicManager* graphicManager;
};

#endif
