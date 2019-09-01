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



WindowManager::WindowManager()
{
  initialized = false;
  window = nullptr;
  windowContext = nullptr;

  eventManager = new EventManager();
}

WindowManager::~WindowManager()
{
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
    std::cout << "> Failed to initialize SDL.\n\tSDL Error: " << SDL_GetError() << std::endl;
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
    std::cout << "> Failed to create window.\n\tSDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "> SDL window created successfully." << std::endl;

  // Get window context
  windowContext = SDL_GL_CreateContext(window);



  // On init

  // Callback
  using namespace std::placeholders; // For argument placeholders of _1, _2, _3
  auto callback = std::bind(&WindowManager::onActionCallback, this, _1, _2, _3);
  eventManager->setOnActionCallback(callback);
  


  initialized = true;
  return initialized;
}

bool WindowManager::update()
{
  if (!eventManager->update())
    return false;
  return true;
}

void WindowManager::drawContext()
{
  // Swap the screen buffers
  SDL_GL_SwapWindow(window);
}



void WindowManager::move(Direction direction)
{
  switch (direction)
  {
  case DIRECTION_NORTH:
    std::cout << "Move to up" << std::endl;
    break;
  case DIRECTION_SOUTH:
    std::cout << "Move to down" << std::endl;
    break;
  case DIRECTION_WEST:
    std::cout << "Move to left" << std::endl;
    break;
  case DIRECTION_EAST:
    std::cout << "Move to right" << std::endl;
    break;

  default:
    break;
  }
}

void WindowManager::rotate(Direction direction)
{
  switch (direction)
  {
  case DIRECTION_NORTH:
    std::cout << "Rotate to up" << std::endl;
    break;
  case DIRECTION_SOUTH:
    std::cout << "Rotate to down" << std::endl;
    break;
  case DIRECTION_WEST:
    std::cout << "Rotate to left" << std::endl;
    break;
  case DIRECTION_EAST:
    std::cout << "Rotate to right" << std::endl;
    break;

  default:
    break;
  }
}

void WindowManager::zoom(Direction direction)
{
  switch (direction)
  {
  case DIRECTION_NORTH:
    std::cout << "Zoom increase" << std::endl;
    break;
  case DIRECTION_SOUTH:
    std::cout << "Zoom decrease" << std::endl;
    break;
  case DIRECTION_WEST:
    std::cout << "Zoom decrease" << std::endl;
    break;
  case DIRECTION_EAST:
    std::cout << "Zoom increase" << std::endl;
    break;

  default:
    break;
  }
}



void WindowManager::changeCamera(Camera /*camera*/ /*= CAMERA_NONE*/)
{
  std::cout << "Change camera" << std::endl;

  // If is CAMERA_NONE, change to the next Camera
}

void WindowManager::changeViewMode(ViewMode /*viewMode*/ /*= VIEWMODE_NONE*/)
{
  std::cout << "Change view mode (Texture / Flat Shade / Wireframe)" << std::endl;

  // If is VIEWMODE_NONE, change to the next ViewMode
}

void WindowManager::changeAnimationSet(uint8_t /*animationSetId*/ /*= 255*/)
{
  std::cout << "Next animation set" << std::endl;

  // If is 255, change to the next AnimationSet
}



void WindowManager::openFile(const std::string& /*path*/)
{
  std::cout << "Opening new file..." << std::endl;
}



void WindowManager::playAnimation()
{
  // ...
}

void WindowManager::stopAnimation()
{
  // ...
}

bool WindowManager::isAnimationPlaying()
{
  // ...
  return true;
}

void WindowManager::toggleAnimation()
{
  std::cout << "Play/Pause" << std::endl;

  if (isAnimationPlaying())
  {
    stopAnimation();
    return;
  }

  playAnimation();
}



uint64_t WindowManager::getFramesCount()
{
  return 0L;
}

uint64_t WindowManager::getFrame()
{
  return 0L;
}

void WindowManager::setFrame(uint64_t /*frameId*/)
{
  // ...
}

void WindowManager::previousFrame()
{
  std::cout << "Step backward 1 frame (up to start)" << std::endl;

  setFrame(std::max(0ULL, getFrame() - 1));
}

void WindowManager::nextFrame()
{
  std::cout << "Step forward 1 frame (up to end)" << std::endl;

  setFrame(std::min(getFrame() + 1, getFramesCount()));
}

void WindowManager::startFrame()
{
  std::cout << "Go to take at start" << std::endl;

  setFrame(0ULL);
}

void WindowManager::endFrame()
{
  std::cout << "Go to take at end" << std::endl;

  setFrame(getFramesCount());
}



void WindowManager::onActionCallback(EventManager* _eventManager, Uint32 eventType, Uint64 action)
{
  Direction direction    = DIRECTION_NONE; // Auxiliar
  SDL_Event eventHandler = _eventManager->getEventHandler();
  Uint16 keyMod          = _eventManager->getKeyModifiers();

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

        // Get direction
        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction);
      }
      // Modifier: Shift
      else if ((keyMod & KMOD_SHIFT) && !(keyMod & (KMOD_CTRL | KMOD_ALT)))
      {
        // Get direction
        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction);
      }
      // No modifier
      else if (!(keyMod & KMOD_KEYS))
      {
        // Get direction
        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          rotate(direction);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          rotate(direction);
      }
    }
    // Holding mouse middle button
    else if (_eventManager->isHoldingMouseMiddleButton())
    {
      // No modifier
      if (!(keyMod & KMOD_KEYS))
      {
        // Get direction
        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction);
        direction = DIRECTION_NONE; // Reset

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          move(direction);
      }
    }
    // Holding mouse right button
    else if (_eventManager->isHoldingMouseRightButton())
    {
      // Modifier: Alt
      if ((keyMod & KMOD_ALT) && !(keyMod & (KMOD_CTRL | KMOD_SHIFT)))
      {
        // Get direction
        // Up
        if (eventHandler.motion.yrel < 0)
          direction = DIRECTION_NORTH;
        // Down
        else if (eventHandler.motion.yrel > 0)
          direction = DIRECTION_SOUTH;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction);
        direction = DIRECTION_NONE;

        // Left
        if (eventHandler.motion.xrel < 0)
          direction = DIRECTION_WEST;
        // Right
        else if (eventHandler.motion.xrel > 0)
          direction = DIRECTION_EAST;

        // Execute
        if (direction != DIRECTION_NONE)
          zoom(direction);
      }
    }
  }

  /* Mouse wheel handling */

  else if (eventType == SDL_MOUSEWHEEL) // Extra
  {
    SDL_MouseWheelEvent wheelEvent = eventHandler.wheel;

    // Get direction
    // Up
    if (wheelEvent.y > 0)
      direction = DIRECTION_NORTH;
    // Down
    else if (wheelEvent.y < 0)
      direction = DIRECTION_SOUTH;

    // Execute
    if (direction != DIRECTION_NONE)
      zoom(direction);
  }

  /* Key handling */

  else if (eventType == SDL_KEYDOWN)
  {
    // Modifier: Ctrl
    if ((keyMod & KMOD_CTRL) && !(keyMod & (KMOD_SHIFT | KMOD_ALT)))
    {
      // Get direction
      // Up
      if (action == SDLK_UP)
        direction = DIRECTION_NORTH;
      // Down
      else if (action == SDLK_DOWN)
        direction = DIRECTION_SOUTH;
      // Left
      else if (action == SDLK_LEFT)
        direction = DIRECTION_WEST;
      // Down
      else if (action == SDLK_RIGHT)
        direction = DIRECTION_EAST;

      // Execute
      if (direction != DIRECTION_NONE)
        zoom(direction);

      // Other shortcuts
      else
        switch (action)
        {
        case SDLK_k:
          changeCamera();
          break;

        case SDLK_m:
          changeViewMode();
          break;

        case SDLK_n:
          changeAnimationSet();
          break;

        case SDLK_o:
          openFile("");
          break;

        case SDLK_p:
          toggleAnimation();
          break;

        default:
          break;
        }
    }
    // Modifier: Shift
    else if ((keyMod & KMOD_SHIFT) && !(keyMod & (KMOD_CTRL | KMOD_ALT)))
    {
      // Get direction
      // Up
      if (action == SDLK_UP)
        direction = DIRECTION_NORTH;
      // Down
      else if (action == SDLK_DOWN)
        direction = DIRECTION_SOUTH;
      // Left
      else if (action == SDLK_LEFT)
        direction = DIRECTION_WEST;
      // Down
      else if (action == SDLK_RIGHT)
        direction = DIRECTION_EAST;

      // Execute
      if (direction != DIRECTION_NONE)
        move(direction);

      // Other shortcuts
      /*
      else
        switch (action)
        {
          // Nothing yet

        default:
          break;
        }
      */
    }
    // Modifier: Alt
    else if ((keyMod & KMOD_ALT) && !(keyMod & (KMOD_CTRL | KMOD_SHIFT)))
    {
      switch (action)
      {
      case SDLK_LEFT:
        previousFrame();
        break;

      case SDLK_RIGHT:
        nextFrame();
        break;

      case SDLK_HOME:
        startFrame();
        break;

      case SDLK_END:
        endFrame();
        break;

      default:
        break;
      }
    }
    // No modifier
    else if (!(keyMod & KMOD_KEYS))
    {
      // Get direction
      // Up
      if (action == SDLK_UP)
        direction = DIRECTION_NORTH;
      // Down
      else if (action == SDLK_DOWN)
        direction = DIRECTION_SOUTH;
      // Left
      else if (action == SDLK_LEFT)
        direction = DIRECTION_WEST;
      // Down
      else if (action == SDLK_RIGHT)
        direction = DIRECTION_EAST;

      // Execute
      if (direction != DIRECTION_NONE)
        rotate(direction);

      // Other shortcuts
      /*
      else
        switch (action)
        {
          // Nothing yet

        default:
          break;
        }
      */
    }
  }
}
