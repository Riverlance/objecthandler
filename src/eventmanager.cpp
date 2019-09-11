/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "eventmanager.h"
#include "const.h"



EventManager::EventManager()
{
  initialized = false;

  onPollEventCallback = nullptr;
  onPumpEventCallback = nullptr;


  
  mouseLeftButton = false;
  mouseRightButton = false;
  mouseMiddleButton = false;

  keyModifiers = KMOD_NONE;

  keyStates = SDL_GetKeyboardState(nullptr);
}

EventManager::~EventManager()
{
  // Unload joysticks
  unloadJoysticks();
}



bool EventManager::init()
{
  initialized = true;
  
  return initialized;
}

bool EventManager::update()
{
  /* Poll Events (for shortcuts, because it executes only once per user action) */

  while (SDL_PollEvent(&eventHandler) != 0)
  {
    uint32_t eventType = eventHandler.type;
    uint16_t eventMod  = eventHandler.key.keysym.mod;



    if (eventType == SDL_QUIT)
    {
      // No callbacks are used in here for be able to quit the application
      std::cout << "Quitting application..." << std::endl;
      return false; // Quit application
    }

    bool shouldExecuteCallback = false;



    /**
      * Our keyModifiers are made for support only KMOD_CTRL, KMOD_SHIFT, KMOD_ALT and KMOD_GUI
      * 
      * Once the user click or release the Ctrl, Shift, Alt or Gui, the keyModifiers flag will be updated.
      * This is needed because, when you will use another eventType that is not key up/down, the eventMod will probably be not what you want.
      * So, the keyModifiers has the real flags of key up/down for the Ctrl, Shift, Alt and Gui.
      */
    if (eventType == SDL_KEYUP || eventType == SDL_KEYDOWN)
    {
      if (eventMod & KMOD_CTRL)  keyModifiers |=  KMOD_CTRL;  // Include Ctrl flag
      else                       keyModifiers &= ~KMOD_CTRL;  // Remove Ctrl flag
      if (eventMod & KMOD_SHIFT) keyModifiers |=  KMOD_SHIFT; // Include Shift flag
      else                       keyModifiers &= ~KMOD_SHIFT; // Remove Shift flag
      if (eventMod & KMOD_ALT)   keyModifiers |=  KMOD_ALT;   // Include Alt flag
      else                       keyModifiers &= ~KMOD_ALT;   // Remove Alt flag
      if (eventMod & KMOD_GUI)   keyModifiers |=  KMOD_GUI;   // Include Gui flag
      else                       keyModifiers &= ~KMOD_GUI;   // Remove Gui flag
    }
    // std::cout << "KeyModifier: " << keyModifiers << std::endl;



    /* Mouse motion handling */
    
    if (eventType == SDL_MOUSEMOTION) // eventHandler.motion.x, eventHandler.motion.y
    {
      if (onPollEventCallback != nullptr)
        onPollEventCallback(this, eventType, KMOD_NONE); // If you want to get eventHandler data, you should get that through the 'this' parameter
    }



    /* Mouse button handling */

    else if (eventType == SDL_MOUSEBUTTONUP || eventType == SDL_MOUSEBUTTONDOWN)
    {
      bool isMouseButtonPressed = eventType == SDL_MOUSEBUTTONDOWN;

      uint8_t mouseButton = eventHandler.button.button;
      switch (mouseButton)
      {
      case SDL_BUTTON_LEFT:
        shouldExecuteCallback = true;
        mouseLeftButton       = isMouseButtonPressed;
        // std::cout << "Mouse left button " << (isMouseButtonPressed ? "down" : "up") << std::endl;
        break;

      case SDL_BUTTON_RIGHT:
        shouldExecuteCallback = true;
        mouseRightButton      = isMouseButtonPressed;
        // std::cout << "Mouse right button " << (isMouseButtonPressed ? "down" : "up") << std::endl;
        break;

      case SDL_BUTTON_MIDDLE:
        shouldExecuteCallback = true;
        mouseMiddleButton     = isMouseButtonPressed;
        // std::cout << "Mouse middle button " << (isMouseButtonPressed ? "down" : "up") << std::endl;
        break;

      default:
        break;
      }

      if (shouldExecuteCallback)
        if (onPollEventCallback != nullptr)
          onPollEventCallback(this, eventType, mouseButton);
    }



    /* Mouse wheel handling */

    else if (eventType == SDL_MOUSEWHEEL)
    {
      SDL_MouseWheelEvent wheelEvent = eventHandler.wheel;
      if (wheelEvent.y > 0)
      {
        shouldExecuteCallback = true;
        // std::cout << "Scroll up" << std::endl;
      }
      else if (wheelEvent.y < 0)
      {
        shouldExecuteCallback = true;
        // std::cout << "Scroll down" << std::endl;
      }

      // We don't give support for left/right wheel.
      /*
      if (wheelEvent.x > 0) // Scroll right
        ;// ...
      else if (wheelEvent.x < 0) // Scroll left
        ;// ...
      */

      if (shouldExecuteCallback)
        if (onPollEventCallback != nullptr)
          onPollEventCallback(this, eventType, KMOD_NONE); // If you want to get eventHandler data, you should get that through the 'this' parameter
    }



    /* Key handling */

    else if (eventType == SDL_KEYUP || eventType == SDL_KEYDOWN)
    {
      SDL_Keycode key = eventHandler.key.keysym.sym;

      // Esc or Ctrl+w
      if (key == SDLK_ESCAPE || (keyModifiers & KMOD_CTRL && key == SDLK_w))
      {
        // No callbacks are used in here for be able to quit the application
        std::cout << "Quitting application..." << std::endl;
        return false; // Quit application
      }

      // Any other key
      if (onPollEventCallback != nullptr)
        onPollEventCallback(this, eventType, key);
    }



    /* Joystick handling */

    else if (eventType == SDL_JOYDEVICEADDED)
    {
      std::cout << "> A new Joystick has been connected." << std::endl;
      loadJoysticks(); // Reload joysticks
    }

    else if (eventType == SDL_JOYDEVICEREMOVED)
    {
      std::cout << "> A Joystick has been disconnected." << std::endl;
      loadJoysticks(); // Reload joysticks
    }

    // Axis
    else if (eventType == SDL_JOYAXISMOTION || eventType == SDL_JOYHATMOTION)
    {
      if (onPollEventCallback != nullptr)
        onPollEventCallback(this, eventType, KMOD_NONE);
    }



    else if (eventType == SDL_JOYBUTTONUP ||  eventType == SDL_JOYBUTTONDOWN)
    {
      if (onPollEventCallback != nullptr)
        onPollEventCallback(this, eventType, eventHandler.jbutton.button);
    }
  }
  


  /* Pump Events (for continuously shortcuts, because it executes while user hold it) */

  SDL_PumpEvents();
  if (onPumpEventCallback != nullptr)
    onPumpEventCallback(this, keyStates);
  
  return true; // Keep running application
}

bool EventManager::loadJoysticks()
{
  // Unload previous joysticks
  unloadJoysticks();

  int joystickCount = SDL_NumJoysticks();
  if (joystickCount < 1)
  {
    std::cout << "> Warning: No joystick connected." << std::endl;
    return false;
  }

  bool error = false;
  for (int i = 0; i < joystickCount; i++)
  {
    SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (joystick == nullptr)
    {
      error = true;
      break;
    }
    joysticks[i] = joystick;
  }

  if (error)
  {
    unloadJoysticks(); // Remove successfully registered joysticks
    std::cerr << "> Failed to initialize a Joystick.\n\tSDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  
  std::cout << "> Joysticks loaded successfully." << std::endl;
  return true;
}

void EventManager::unloadJoysticks()
{
  for (const auto& it : joysticks)
    SDL_JoystickClose(it.second);
  joysticks.clear();
}
