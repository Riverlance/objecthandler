/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <SDL.h>
#include "eventmanager.h"
#include "graphicmanager.h"
#include "const.h"



class WindowManager
{
  public:
    // Initialize
    WindowManager();

    // Deallocate memory
    ~WindowManager();

    // Prevent clone this object
    WindowManager(const WindowManager&) = delete; // Prevent construction by copying
    WindowManager& operator=(const WindowManager&) = delete; // Prevent assignment



    bool init();
    bool update();
    void drawContext();



    /**
      * Singleton implementation.
      *
      * @return a SDL window handler singleton
      */
    static WindowManager* getInstance()
    {
      static WindowManager instance;
      return &instance;
    };
    
    bool isInitialized() { return initialized; }

    SDL_Window* getWindow() { return window; }
    SDL_GLContext getWindowContext() { return windowContext; }

    EventManager* getEventManager() { return eventManager; }

    GraphicManager* getGraphicManager() { return graphicManager; }

    void move(Direction_t direction, Device_t device);
    void rotate(Direction_t direction, Device_t device);
    void zoom(Direction_t direction, Device_t device);

    void changeCamera(Camera_t cameraType = CAMERA_NONE);
    void changeViewMode(ViewMode_t viewMode = VIEWMODE_NONE);

    void openFile(const std::string& path);

    void onPollEventCallback(EventManager* _eventManager, uint32_t eventType, uint64_t action);
    void onPumpEventCallback(EventManager* _eventManager, const uint8_t* keyStates);



  private:
    bool initialized;



    // Window we'll be rendering to
    SDL_Window* window;

    // Context contained by the window
    SDL_GLContext windowContext;

    EventManager* eventManager;

    GraphicManager* graphicManager;
    GLfloat currentFrame;
    GLfloat lastFrame;
    GLfloat deltaTime;



    GLfloat moveMouseSensitivity;
    GLfloat rotateMouseSensitivity;
    GLfloat zoomMouseSensitivity;
    GLfloat moveKeyboardSensitivity;
    GLfloat rotateKeyboardSensitivity;
    GLfloat zoomKeyboardSensitivity;
    GLfloat moveJoystickSensitivity;
    GLfloat rotateJoystickSensitivity;
    GLfloat zoomJoystickSensitivity;
    uint8_t joystickAxis1;
    uint8_t joystickAxis2;
    uint8_t joystickAxisCross;
    bool joystickL2;
    bool joystickR2;
};
