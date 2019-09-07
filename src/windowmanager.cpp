/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "windowmanager.h"
#include "eventmanager.h"
#include "graphicmanager.h"
#include <SDL.h>
#include "const.h"



WindowManager::WindowManager() :
  moveMouseSensitivity(DEFAULT_MOUSE_SENSITIVITY_MOVE),
  rotateMouseSensitivity(DEFAULT_MOUSE_SENSITIVITY_ROTATE),
  zoomMouseSensitivity(DEFAULT_MOUSE_SENSITIVITY_ZOOM),
  moveKeyboardSensitivity(DEFAULT_KEYBOARD_SENSITIVITY_MOVE),
  rotateKeyboardSensitivity(DEFAULT_KEYBOARD_SENSITIVITY_ROTATE),
  zoomKeyboardSensitivity(DEFAULT_KEYBOARD_SENSITIVITY_ZOOM)
{
  initialized = false;
  window = nullptr;
  windowContext = nullptr;

  eventManager = new EventManager();
}

WindowManager::~WindowManager()
{
  // Destroy graphic manager
  graphicManager->~GraphicManager();

  // Deallocate context
  if (windowContext != nullptr)
  {
    SDL_GL_DeleteContext(windowContext);
    windowContext = nullptr;
  }

  // Destroy window
  if (window != nullptr)
  {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  // Quit SDL subsystems
  SDL_Quit();

  // Since is a Singleton class, we should clear all vars because this object is never deleted
  initialized = false;
}

bool WindowManager::init()
{
  std::cout << std::endl;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cerr << "> Failed to initialize SDL.\n\tSDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "> SDL initialized successfully." << std::endl;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // OpenGL core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // OpenGL 3
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // OpenGL 3.3
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // Stencil buffer size

  // Create window
  window = SDL_CreateWindow(STATUS_APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == nullptr)
  {
    std::cerr << "> Failed to create window.\n\tSDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "> SDL window created successfully." << std::endl;

  // Get window context
  windowContext = SDL_GL_CreateContext(window);

  // Graphic manager
  graphicManager = GraphicManager::getInstance();
  if (!graphicManager->init())
    return false;



  // On init

  // Callback
  using namespace std::placeholders; // For argument placeholders of _1, _2, _3
  auto pollCallback = std::bind(&WindowManager::onPollEventCallback, this, _1, _2, _3);
  eventManager->setOnPollEventCallback(pollCallback);
  auto pumpCallback = std::bind(&WindowManager::onPumpEventCallback, this, _1, _2);
  eventManager->setOnPumpEventCallback(pumpCallback);
  


  initialized = true;
  return initialized;
}

bool WindowManager::update()
{
  currentFrame = (GLfloat)SDL_GetTicks();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // Events
  if (!eventManager->update())
    return false;

  // Context
  graphicManager->update();

  return true;
}

void WindowManager::drawContext()
{
  // Swap the screen buffers
  SDL_GL_SwapWindow(window);
}



void WindowManager::move(Direction_t direction, bool isFromMouse /*= false*/)
{
  graphicManager->getCamera()->move(direction, (isFromMouse ? moveMouseSensitivity : moveKeyboardSensitivity) * deltaTime);
}

void WindowManager::rotate(Direction_t direction, bool isFromMouse /*= false*/)
{
  graphicManager->getCamera()->rotate(direction, (isFromMouse ? rotateMouseSensitivity : rotateKeyboardSensitivity) * deltaTime, false);
}

void WindowManager::zoom(Direction_t direction, bool isFromMouse /*= false*/)
{
  graphicManager->getCamera()->zoom(direction, (isFromMouse ? zoomMouseSensitivity : zoomKeyboardSensitivity) * deltaTime);
}



void WindowManager::changeCamera(Camera_t cameraType /*= CAMERA_NONE*/)
{
  graphicManager->getCamera()->updateCamera(cameraType, DEFAULT_CAMERA_DISTANCE);
}

void WindowManager::changeViewMode(ViewMode /*viewMode*/ /*= VIEWMODE_NONE*/)
{
  std::cout << "Change view mode (Texture / Flat Shade / Wireframe)" << std::endl;

  // If is VIEWMODE_NONE, change to the next ViewMode
}



void WindowManager::openFile(const std::string& /*path*/)
{
  std::cout << "Opening new file..." << std::endl;
}



void WindowManager::onPollEventCallback(EventManager* _eventManager, Uint32 eventType, Uint64 action)
{
  Direction_t direction  = DIRECTION_NONE; // Helper
  SDL_Event eventHandler = _eventManager->getEventHandler(); // Poll
  Uint16 keyMod          = _eventManager->getKeyModifiers(); // Work for poll and pump



  /* Mouse motion handling */

  if (eventType == SDL_MOUSEMOTION)
  {
    // Holding mouse left button
    if (_eventManager->isHoldingMouseLeftButton())
    {
      // Modifier: Ctrl
      if ((keyMod & KMOD_CTRL) && !(keyMod & (KMOD_SHIFT | KMOD_ALT)))
      {
        //std::cout << "x: " << eventHandler.motion.xrel << " | y: " << eventHandler.motion.yrel << std::endl;

        // Zoom

        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, true);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, true);
      }

      // Modifier: Shift
      else if ((keyMod & KMOD_SHIFT) && !(keyMod & (KMOD_CTRL | KMOD_ALT)))
      {
        // Move

        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, true);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, true);
      }

      // No modifier
      else if (!(keyMod & KMOD_KEYS))
      {
        // Rotate

        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          rotate(direction, true);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          rotate(direction, true);
      }
    }
    
    // Holding mouse middle button
    else if (_eventManager->isHoldingMouseMiddleButton())
    {
      // No modifier
      if (!(keyMod & KMOD_KEYS))
      {
        // Move

        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, true);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, true);
      }
    }
    
    // Holding mouse right button
    else if (_eventManager->isHoldingMouseRightButton())
    {
      // Modifier: Alt
      if ((keyMod & KMOD_ALT) && !(keyMod & (KMOD_CTRL | KMOD_SHIFT)))
      {
        // Zoom

        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, true);
        direction = DIRECTION_NONE;

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, true);
      }
    }
  }



  /* Mouse wheel handling */

  else if (eventType == SDL_MOUSEWHEEL)
  {
    SDL_MouseWheelEvent wheelEvent = eventHandler.wheel;

    // Zoom

    // Up
    if (wheelEvent.y > 0)
      direction = DIRECTION_NORTH;
    // Down
    else if (wheelEvent.y < 0)
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      zoom(direction, true);
  }



  /* Key handling */

  else if (eventType == SDL_KEYDOWN)
  {
    // Modifier: Ctrl
    if ((keyMod & KMOD_CTRL) && !(keyMod & (KMOD_SHIFT | KMOD_ALT)))
    {
        switch (action)
        {
        // Change to next camera
        case SDLK_k:
          changeCamera();
          break;

        // Change to next view mode
        case SDLK_m:
          changeViewMode();
          break;

        // Load a model file
        case SDLK_o:
          openFile("");
          break;

        default:
          break;
        }
    }

    // No modifier
    else if (!(keyMod & KMOD_KEYS))
    {
      // Set camera position

      Camera_t cameraType = CAMERA_NONE;
      switch (action)
      {
      // Change to front camera
      case SDLK_KP_8:
        cameraType = CAMERA_FRONT;
        break;
      // Change to right camera
      case SDLK_KP_4:
        cameraType = CAMERA_RIGHT;
        break;
      // Change to back camera
      case SDLK_KP_2:
        cameraType = CAMERA_BACK;
        break;
      // Change to left camera
      case SDLK_KP_6:
        cameraType = CAMERA_LEFT;
        break;

      // Change to bottom camera
      case SDLK_KP_MINUS:
        cameraType = CAMERA_BOTTOM;
        break;
      // Change to top camera
      case SDLK_KP_PLUS:
        cameraType = CAMERA_TOP;
        break;
      // Change to diagonal camera
      case SDLK_KP_DIVIDE:
        cameraType = CAMERA_DIAGONAL;
        break;
      // Change to next camera
      case SDLK_KP_MULTIPLY:
        changeCamera();
        break;

      default:
        break;
      }

      // Execute
      if (cameraType != CAMERA_NONE)
        changeCamera(cameraType);
    }
  }
}

void WindowManager::onPumpEventCallback(EventManager* _eventManager, const Uint8* keyStates)
{
  Direction_t direction = DIRECTION_NONE; // Helper
  Uint16 keyMod         = _eventManager->getKeyModifiers(); // Work for poll and pump



  /* Key handling */
  
  // Modifier: Ctrl
  if ((keyMod & KMOD_CTRL) && !(keyMod & (KMOD_SHIFT | KMOD_ALT)))
  {
    // Zoom

    // Up
    if (keyStates[SDL_SCANCODE_UP])
      direction = DIRECTION_NORTH;
    // Down
    else if (keyStates[SDL_SCANCODE_DOWN])
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      zoom(direction, false);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Down
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      zoom(direction, false);
  }
  
  // Modifier: Shift
  else if ((keyMod & KMOD_SHIFT) && !(keyMod & (KMOD_CTRL | KMOD_ALT)))
  {
    // Move

    // Up
    if (keyStates[SDL_SCANCODE_UP])
      direction = DIRECTION_NORTH;
    // Down
    else if (keyStates[SDL_SCANCODE_DOWN])
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, false);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, false);
  }
  
  // No modifier
  else if (!(keyMod & KMOD_KEYS))
  {
    // Rotate

    // Up
    if (keyStates[SDL_SCANCODE_UP])
      direction = DIRECTION_NORTH;
    // Down
    else if (keyStates[SDL_SCANCODE_DOWN])
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      rotate(direction, false);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      rotate(direction, false);
    direction = DIRECTION_NONE; // Reset
    


    // Move

    // Up
    if (keyStates[SDL_SCANCODE_W])
      direction = DIRECTION_NORTH;
    // Down
    else if (keyStates[SDL_SCANCODE_S])
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, false);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_A])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_D])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, false);
  }
}
