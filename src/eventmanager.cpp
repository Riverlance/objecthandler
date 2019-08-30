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

  onActionCallback = nullptr;


  
  mouseLeftButton = false;
  mouseRightButton = false;
  mouseMiddleButton = false;

  keyModifiers = KMOD_NONE;

  //keyStates = SDL_GetKeyboardState(nullptr);

  gameJoystick = nullptr;

  init();
}

EventManager::~EventManager()
{
  if (gameJoystick != nullptr)
  {
    SDL_JoystickClose(gameJoystick);
    gameJoystick = nullptr;
  }
}



bool EventManager::init()
{
  initialized = true;

  loadJoystick();

  return initialized;
}

bool EventManager::update()
{
  /* Poll Events (for shortcuts, because it executes only once per user action) */

  while (SDL_PollEvent(&eventHandler) != 0)
  {
    Uint32 eventType = eventHandler.type;
    Uint16 eventMod  = eventHandler.key.keysym.mod;



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
      if (onActionCallback != nullptr)
        onActionCallback(this, eventType, KMOD_NONE); // If you want to get eventHandler data, you should get that through the 'this' parameter
    }



    /* Mouse button handling */

    else if (eventType == SDL_MOUSEBUTTONUP || eventType == SDL_MOUSEBUTTONDOWN)
    {
      bool isMouseButtonPressed = eventType == SDL_MOUSEBUTTONDOWN;

      Uint8 mouseButton = eventHandler.button.button;
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
        if (onActionCallback != nullptr)
          onActionCallback(this, eventType, mouseButton);
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
        if (onActionCallback != nullptr)
          onActionCallback(this, eventType, KMOD_NONE); // If you want to get eventHandler data, you should get that through the 'this' parameter
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
      else
        shouldExecuteCallback = true;

      if (shouldExecuteCallback)
        if (onActionCallback != nullptr)
          onActionCallback(this, eventType, key);
    }



    else if (eventType == SDL_JOYAXISMOTION /*|| eventType == SDL_JOYHATMOTION || eventType == SDL_JOYHATMOTION*/)
    {
      // Update
      /*
      int xDirection = 0;
      int yDirection = 0;

      // Joystick 0
      if (eventHandler.jaxis.which == 0)
      {
        // X axis motion
        if (eventHandler.jaxis.axis == 0)
          //xDirection = eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE ? -1 : (eventHandler.jaxis.value > eventHandler.jaxis.value ? 1 : 0);
          if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
            xDirection = -1;
          else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
            xDirection = 1;
          else
            xDirection = 0;
        // Y axis motion
        else if (eventHandler.jaxis.axis == 1)
          //yDirection = eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE ? -1 : (eventHandler.jaxis.value > eventHandler.jaxis.value ? 1 : 0);
          if (eventHandler.jaxis.value < -JOYSTICK_DEAD_ZONE)
            yDirection = -1;
          else if (eventHandler.jaxis.value > JOYSTICK_DEAD_ZONE)
            yDirection = 1;
          else
            yDirection = 0;
      }
      std::cout << "[xDir: " << xDirection << "] [yDir: " << yDirection << "]" << std::endl;
      */
    }



    else if (eventType == SDL_JOYBUTTONUP ||  eventType == SDL_JOYBUTTONDOWN)
    {
      // Update
      /*
      std::cout << "joy button " << (int) eventHandler.jbutton.button << std::endl;
      */
    }
  }
  


  /* Pump Events (for continuously shortcuts, because it executes while user hold it) */

  // Update
  /*
  SDL_PumpEvents();
  if (keyStates[SDL_GetScancodeFromKey(SDLK_UP)])
  {
    std::cout << "Mod: ";
    if (keyModifiers & KMOD_CTRL)
      std::cout << "CTRL";
    if (keyModifiers & KMOD_SHIFT)
      std::cout << "SHIFT";
    if (keyModifiers & KMOD_ALT)
      std::cout << "ALT";
    std::cout << std::endl;

    // onMovementCallback(this, SDLK_UP)
  }
  */
  
  return true; // Keep running application
}

bool EventManager::loadJoystick()
{
  if (SDL_NumJoysticks() < 1)
  {
    std::cout << "> Warning: No joystick connected." << std::endl;
    return false;
  }

  gameJoystick = SDL_JoystickOpen(0); // First joystick
  if (gameJoystick == nullptr)
  {
    std::cout << "> Failed to initialize Game Joystick.\n\tSDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  std::cout << "> Game Joystick loaded successfully." << std::endl;
  return true;
}
