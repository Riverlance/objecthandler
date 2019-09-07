/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
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

    void move(Direction_t direction, bool isFromMouse = false);
    void rotate(Direction_t direction, bool isFromMouse = false);
    void zoom(Direction_t direction, bool isFromMouse = false);

    void changeCamera(Camera_t cameraType = CAMERA_NONE);
    void changeViewMode(ViewMode viewMode = VIEWMODE_NONE);
    void changeAnimationSet(uint8_t animationSetId = 255);

    void openFile(const std::string& path);

    void playAnimation();
    void stopAnimation();
    bool isAnimationPlaying();
    void toggleAnimation();

    uint64_t getFramesCount();
    uint64_t getFrame();
    void setFrame(uint64_t frameId);
    void previousFrame();
    void nextFrame();
    void startFrame();
    void endFrame();
    
    void onActionCallback(EventManager* _eventManager, Uint32 eventType, Uint64 action);



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
};
