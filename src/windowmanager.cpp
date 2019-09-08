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
  zoomKeyboardSensitivity(DEFAULT_KEYBOARD_SENSITIVITY_ZOOM),
  moveJoystickSensitivity(DEFAULT_JOYSTICK_SENSITIVITY_MOVE),
  rotateJoystickSensitivity(DEFAULT_JOYSTICK_SENSITIVITY_ROTATE),
  zoomJoystickSensitivity(DEFAULT_JOYSTICK_SENSITIVITY_ZOOM),
  joystickAxis1(DIRECTION_NONE),
  joystickAxis2(DIRECTION_NONE),
  joystickAxisCross(DIRECTION_NONE),
  joystickL2(false),
  joystickR2(false)
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
  std::cout << std::endl;

  // Get window context
  windowContext = SDL_GL_CreateContext(window);

  // Graphic manager
  graphicManager = GraphicManager::getInstance();
  if (!graphicManager->init())
    return false;

  // Event manager
  eventManager->init();



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



  // Joystick

  // Axis 1

  if (joystickAxis1 != DIRECTION_NONE)
  {
    // X
    if (joystickAxis1 & DIRECTION_WEST)
      move(DIRECTION_WEST, DEVICE_JOYSTICK);
    else if (joystickAxis1 & DIRECTION_EAST)
      move(DIRECTION_EAST, DEVICE_JOYSTICK);

    // Y
    if (joystickAxis1 & DIRECTION_NORTH)
      move(DIRECTION_NORTH, DEVICE_JOYSTICK);
    else if (joystickAxis1 & DIRECTION_SOUTH)
      move(DIRECTION_SOUTH, DEVICE_JOYSTICK);
  }

  if (joystickL2 == true)
    zoom(DIRECTION_SOUTH, DEVICE_JOYSTICK);

  // Axis 2

  if (joystickAxis2 != DIRECTION_NONE)
  {
    // X
    if (joystickAxis2 & DIRECTION_WEST)
      rotate(DIRECTION_WEST, DEVICE_JOYSTICK);
    else if (joystickAxis2 & DIRECTION_EAST)
      rotate(DIRECTION_EAST, DEVICE_JOYSTICK);

    // Y
    if (joystickAxis2 & DIRECTION_NORTH)
      rotate(DIRECTION_NORTH, DEVICE_JOYSTICK);
    else if (joystickAxis2 & DIRECTION_SOUTH)
      rotate(DIRECTION_SOUTH, DEVICE_JOYSTICK);
  }

  if (joystickR2 == true)
    zoom(DIRECTION_NORTH, DEVICE_JOYSTICK);

  // Axis cross

  if (joystickAxisCross != DIRECTION_NONE)
  {
    // X
    if (joystickAxisCross & DIRECTION_WEST)
      move(DIRECTION_WEST, DEVICE_JOYSTICK);
    else if (joystickAxisCross & DIRECTION_EAST)
      move(DIRECTION_EAST, DEVICE_JOYSTICK);

    // Y
    if (joystickAxisCross & DIRECTION_NORTH)
      move(DIRECTION_NORTH, DEVICE_JOYSTICK);
    else if (joystickAxisCross & DIRECTION_SOUTH)
      move(DIRECTION_SOUTH, DEVICE_JOYSTICK);
  }



  return true;
}

void WindowManager::drawContext()
{
  // Swap the screen buffers
  SDL_GL_SwapWindow(window);
}



void WindowManager::move(Direction_t direction, Device_t device)
{
  GLfloat sensitivity = 0.0f;
  if (device & DEVICE_MOUSE)
    sensitivity = moveMouseSensitivity;
  else if (device & DEVICE_KEYBOARD)
    sensitivity = moveKeyboardSensitivity;
  else if (device & DEVICE_JOYSTICK)
    sensitivity = moveJoystickSensitivity;

  if (sensitivity > 0.0f)
    graphicManager->getCamera()->move(direction, sensitivity * deltaTime);
}

void WindowManager::rotate(Direction_t direction, Device_t device)
{
  GLfloat sensitivity = 0.0f;
  if (device & DEVICE_MOUSE)
    sensitivity = rotateMouseSensitivity;
  else if (device & DEVICE_KEYBOARD)
    sensitivity = rotateKeyboardSensitivity;
  else if (device & DEVICE_JOYSTICK)
    sensitivity = rotateJoystickSensitivity;

  if (sensitivity > 0.0f)
    graphicManager->getCamera()->rotate(direction, sensitivity * deltaTime, false);
}

void WindowManager::zoom(Direction_t direction, Device_t device)
{
  GLfloat sensitivity = 0.0f;
  if (device & DEVICE_MOUSE)
    sensitivity = zoomMouseSensitivity;
  else if (device & DEVICE_KEYBOARD)
    sensitivity = zoomKeyboardSensitivity;
  else if (device & DEVICE_JOYSTICK)
    sensitivity = zoomJoystickSensitivity;

  if (sensitivity > 0.0f)
    graphicManager->getCamera()->zoom(direction, sensitivity * deltaTime);
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
          zoom(direction, DEVICE_MOUSE);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, DEVICE_MOUSE);
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
          move(direction, DEVICE_MOUSE);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, DEVICE_MOUSE);
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
          rotate(direction, DEVICE_MOUSE);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          rotate(direction, DEVICE_MOUSE);
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
          move(direction, DEVICE_MOUSE);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction, DEVICE_MOUSE);
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
          zoom(direction, DEVICE_MOUSE);
        direction = DIRECTION_NONE;

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction, DEVICE_MOUSE);
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
      zoom(direction, DEVICE_MOUSE);
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



  /* Joystick handling */

  else if (eventType == SDL_JOYAXISMOTION)
  {
    // Joystick 0
    //if (eventHandler.jaxis.which == 0)
    //{
      // Axis 1

      // X
      if (eventHandler.jaxis.axis == 0)
      {
        if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
          joystickAxis1 |= DIRECTION_WEST;
        else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickAxis1 |= DIRECTION_EAST;
        else
        {
          joystickAxis1 &= ~DIRECTION_WEST;
          joystickAxis1 &= ~DIRECTION_EAST;
        }
      }

      // Y
      if (eventHandler.jaxis.axis == 1)
      {
        if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
          joystickAxis1 |= DIRECTION_NORTH;
        else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickAxis1 |= DIRECTION_SOUTH;
        else
        {
          joystickAxis1 &= ~DIRECTION_NORTH;
          joystickAxis1 &= ~DIRECTION_SOUTH;
        }
      }

      // L2
      if (eventHandler.jaxis.axis == 2)
      {
        if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickL2 = true;
        else
          joystickL2 = false;
      }



      // Axis 2 (if it has)

      // X
      if (eventHandler.jaxis.axis == 3)
      {
        if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
          joystickAxis2 |= DIRECTION_WEST;
        else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickAxis2 |= DIRECTION_EAST;
        else
        {
          joystickAxis2 &= ~DIRECTION_WEST;
          joystickAxis2 &= ~DIRECTION_EAST;
        }
      }

      // Y
      if (eventHandler.jaxis.axis == 4)
      {
        if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
          joystickAxis2 |= DIRECTION_NORTH;
        else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickAxis2 |= DIRECTION_SOUTH;
        else
        {
          joystickAxis2 &= ~DIRECTION_NORTH;
          joystickAxis2 &= ~DIRECTION_SOUTH;
        }
      }

      // R2
      if (eventHandler.jaxis.axis == 5)
      {
        if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
          joystickR2 = true;
        else
          joystickR2 = false;
      }
    //}
  }

  else if (eventType == SDL_JOYHATMOTION)
  {
    // Axis cross

    // X
    if (eventHandler.jhat.value & SDL_HAT_LEFT)
      joystickAxisCross |= DIRECTION_WEST;
    else if (eventHandler.jhat.value & SDL_HAT_RIGHT)
      joystickAxisCross |= DIRECTION_EAST;
    else
    {
      joystickAxisCross &= DIRECTION_WEST;
      joystickAxisCross &= DIRECTION_EAST;
    }



    // Y
    if (eventHandler.jhat.value & SDL_HAT_UP)
      joystickAxisCross |= DIRECTION_NORTH;
    else if (eventHandler.jhat.value & SDL_HAT_DOWN)
      joystickAxisCross |= DIRECTION_SOUTH;
    else
    {
      joystickAxisCross &= ~DIRECTION_NORTH;
      joystickAxisCross &= ~DIRECTION_SOUTH;
    }
  }

  else if (eventType == SDL_JOYBUTTONDOWN)
  {
    //std::cout << action << std::endl;

    switch (action)
    {
    // X
    case 0:
      changeCamera(CAMERA_BACK);
      break;
    // O
    case 1:
      changeCamera(CAMERA_LEFT);
      break;
    // Square
    case 2:
      changeCamera(CAMERA_RIGHT);
      break;
    // Triangle
    case 3:
      changeCamera(CAMERA_FRONT);
      break;

    // L1
    case 4:
      changeCamera(CAMERA_TOP);
      break;
    // R1
    case 5:
      changeCamera(CAMERA_BOTTOM);
      break;

    // Select / Share
    case 6:
      changeCamera();
      break;
    // Start / Options
    case 7:
      changeCamera(CAMERA_DIAGONAL);
      break;

    default:
      break;
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
      zoom(direction, DEVICE_KEYBOARD);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Down
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      zoom(direction, DEVICE_KEYBOARD);
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
      move(direction, DEVICE_KEYBOARD);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, DEVICE_KEYBOARD);
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
      rotate(direction, DEVICE_KEYBOARD);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_LEFT])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_RIGHT])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      rotate(direction, DEVICE_KEYBOARD);
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
      move(direction, DEVICE_KEYBOARD);
    direction = DIRECTION_NONE; // Reset

    // Left
    if (keyStates[SDL_SCANCODE_A])
      direction = DIRECTION_WEST;
    // Right
    else if (keyStates[SDL_SCANCODE_D])
      direction = DIRECTION_EAST;

    // Execute
    if (direction != DIRECTION_NONE)
      move(direction, DEVICE_KEYBOARD);
  }
}
