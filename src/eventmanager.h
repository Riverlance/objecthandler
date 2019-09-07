/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <SDL.h>



class EventManager
{
  public:
    // Initialize
    EventManager();

    // Deallocate memory
    ~EventManager();

    // Prevent clone this object
    EventManager(const EventManager&) = delete; // Prevent construction by copying
    EventManager& operator=(const EventManager&) = delete; // Prevent assignment



    bool init();
    bool update();
    bool loadJoystick();



    bool isInitialized() { return initialized; }
    SDL_Event getEventHandler() { return eventHandler; }
    bool isHoldingMouseLeftButton() { return mouseLeftButton; }
    bool isHoldingMouseRightButton() { return mouseRightButton; }
    bool isHoldingMouseMiddleButton() { return mouseMiddleButton; }
    Uint16 getKeyModifiers() { return keyModifiers; }

    void setOnPollEventCallback(std::function<void(EventManager*, Uint32, Uint64)> _onPollEventCallback) { onPollEventCallback = _onPollEventCallback; }
    void setOnPumpEventCallback(std::function<void(EventManager*, const Uint8*)> _onPumpEventCallback) { onPumpEventCallback = _onPumpEventCallback; }
    


    private:
      bool initialized;
      


      /* Registered input */

      bool mouseLeftButton;
      bool mouseRightButton;
      bool mouseMiddleButton;

      Uint16 keyModifiers;

      // Poll
      SDL_Event eventHandler;

      // Pump
      const Uint8* keyStates;

      SDL_Joystick* gameJoystick;



      std::function<void(EventManager*, Uint32, Uint64)> onPollEventCallback;
      std::function<void(EventManager*, const Uint8*)> onPumpEventCallback;
};
