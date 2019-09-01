/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef CONST_H
#define CONST_H

#include "graphicmanager.h"

#define STATUS_APP_NAME    "Object Handler"
#define STATUS_APP_VERSION "1.0"
#define STATUS_DEVELOPERS  "Gabriel Moraes de Oliveira"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    32 // Bits Per Pixel

#define KMOD_KEYS   (KMOD_CTRL | KMOD_SHIFT | KMOD_ALT | KMOD_GUI)

//static constexpr GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;



// Theme

enum Theme : char // uint8_t
{
  THEME_LIGHT,
  THEME_DARK,

  THEME_DEFAULT = THEME_DARK,
  THEME_FIRST = THEME_LIGHT,
  THEME_LAST = THEME_DARK,
};
extern Theme APP_THEME;

extern GLclampf THEME_CLEARCOLOR_R;
extern GLclampf THEME_CLEARCOLOR_G;
extern GLclampf THEME_CLEARCOLOR_B;
extern GLclampf THEME_CLEARCOLOR_A;



enum Direction : char // uint8_t
{
  DIRECTION_NORTH = 0,
  DIRECTION_EAST = 1,
  DIRECTION_SOUTH = 2,
  DIRECTION_WEST = 3,

  DIRECTION_DIAGONAL_MASK = 4,

  DIRECTION_SOUTHWEST = DIRECTION_DIAGONAL_MASK | 0,
  DIRECTION_SOUTHEAST = DIRECTION_DIAGONAL_MASK | 1,
  DIRECTION_NORTHWEST = DIRECTION_DIAGONAL_MASK | 2,
  DIRECTION_NORTHEAST = DIRECTION_DIAGONAL_MASK | 3,

  DIRECTION_LAST = DIRECTION_NORTHEAST,
  DIRECTION_NONE = 8,
};

enum Camera : char // uint8_t
{
  CAMERA_NONE,

  CAMERA_FRONT, // Camera at Z looking to center
  CAMERA_RIGHT, // Camera at X looking to center
  CAMERA_BACK,  // Camera at -Z looking to center
  CAMERA_LEFT,  // Camera at -X looking to center

  CAMERA_TOP,    // Camera at Y looking to center
  CAMERA_BOTTOM, // Camera at -Y looking to center

  CAMERA_PERSPECTIVE, // Camera between X, Y and Z looking to center

  CAMERA_LAST = CAMERA_PERSPECTIVE,
};

enum ViewMode : char // uint8_t
{
  VIEWMODE_TEXTURE = 0,
  VIEWMODE_FLATSHADE = 1,
  VIEWMODE_WIREFRAME = 2,

  VIEWMODE_LAST = VIEWMODE_WIREFRAME,
  VIEWMODE_NONE = 3,
};

#endif
