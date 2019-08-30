/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "app.h"
#include "const.h"
#include "windowmanager.h"



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


  
  /*
  // Allow to continue the loading
  // Press any key to continue. . .
#ifdef _WIN32
  system("pause");
#else
  system("read");
#endif
  */



  // Window
  //GWindow* window = new GWindow();
  WindowManager* window = WindowManager::getInstance();
  if (!window->init())
    return false;



  // Force calling destructor method, since we cannot delete a singleton object
  window->~WindowManager();
  //delete window; // You cannot remove a singleton object



  initialized = true;
  return initialized;
}
