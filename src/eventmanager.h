/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL.h>



// Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;



class EventManager
{
  public:
    // Initialize variables
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

    void setOnActionCallback(std::function<void(EventManager*, Uint32, Uint64)> _onActionCallback) { onActionCallback = _onActionCallback; }
    


    private:
      bool initialized;

      SDL_Event eventHandler;



      /* Registered input */

      bool mouseLeftButton;
      bool mouseRightButton;
      bool mouseMiddleButton;

      Uint16 keyModifiers;

      //const Uint8* keyStates;

      SDL_Joystick* gameJoystick;



      std::function<void(EventManager*, Uint32, Uint64)> onActionCallback;
};

#endif
