/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "app.h"



/**
 * Go to Project Properties > Configuration Properties > Linker > System.
 * If you want to load with the Console, set the variable 'SubSystem' to this value: Console (/SUBSYSTEM:CONSOLE)
 * If you want to load without, set to this value: Windows (/SUBSYSTEM:WINDOWS)
 */
int main(int argc, char* argv[])
{
  // Init app
  GApp* g_app = GApp::getInstance();
  if (!g_app->init(argc, argv))
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}
