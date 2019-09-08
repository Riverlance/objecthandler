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
    bool loadJoysticks();
    void unloadJoysticks();



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

      // Joysticks (the one configured here is: Sony Wireless Joystick Dualshock 4 - Model CUH-ZCT2U - Red (need to download and install DS4 Windows at http://ds4windows.com/)
      std::map<int, SDL_Joystick*> joysticks;



      std::function<void(EventManager*, Uint32, Uint64)> onPollEventCallback;
      std::function<void(EventManager*, const Uint8*)> onPumpEventCallback;
};
