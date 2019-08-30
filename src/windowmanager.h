/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SDL.h>
#include "eventmanager.h"
#include "const.h"



class WindowManager
{
  public:
    // Initialize variables
    WindowManager();

    // Deallocate memory
    ~WindowManager();

    // Prevent clone this object
    WindowManager(const WindowManager&) = delete; // Prevent construction by copying
    WindowManager& operator=(const WindowManager&) = delete; // Prevent assignment



    bool init();
    void update();



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
    SDL_Surface* getWindowSurface() { return windowSurface; }

    void move(Direction direction);
    void rotate(Direction direction);
    void zoom(Direction direction);

    void changeCamera(Camera camera = CAMERA_NONE);
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
    


  private:
    void onInit();
    void onActionCallback(EventManager* eventManager, Uint32 eventType, Uint64 action);



    bool initialized;

    // Window we'll be rendering to
    SDL_Window* window;

    // Surface contained by the window
    SDL_Surface* windowSurface;
};

#endif
