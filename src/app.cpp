/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "app.h"
#include "util.h"



Theme_t APP_THEME = DEFAULT_THEME;

GApp::GApp()
{
  initialized = false;

  // Header

  std::cout << STATUS_APP_NAME << " - Version " << STATUS_APP_VERSION << std::endl;
  std::cout << std::endl;

  std::cout << "An Object Handler developed by " << STATUS_DEVELOPERS << std::endl;
  std::cout << std::endl;
}

GApp::~GApp()
{
  initialized = false;
}

bool GApp::init(int /*argc*/, char*[] /*argv*/)
{
  std::cout << ">> Loading core..." << std::endl;
    
  // SDL window
  //GWindow* window = new GWindow();
  windowManager = WindowManager::getInstance();
  if (!windowManager->init())
    return false;

  std::cout << std::endl;
  
  /*
  // Allow to continue the loading
  // Press any key to continue. . .
#ifdef _WIN32
  system("pause");
#else
  system("read");
#endif
  */



  // Default theme
  Util::setTheme(DEFAULT_THEME);



  // Application loop

  while (true) // FPS
  {
    // Window
    if (!windowManager->update())
      break;
    windowManager->drawContext();
  }



  // Force calling destructor method, since we cannot delete a singleton object
  windowManager->~WindowManager();
  //delete window; // You cannot remove a singleton object



  initialized = true;
  return initialized;
}
