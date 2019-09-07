/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <GL/glew.h>



#define STATUS_APP_NAME    "Object Handler"
#define STATUS_APP_VERSION "1.0"
#define STATUS_DEVELOPERS  "Gabriel Moraes de Oliveira"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define SCREEN_BPP    32 // Bits Per Pixel

#define KMOD_KEYS   (KMOD_CTRL | KMOD_SHIFT | KMOD_ALT | KMOD_GUI)



// Theme

enum Theme_t : char // uint8_t
{
  THEME_LIGHT,
  THEME_DARK,

  THEME_DEFAULT = THEME_DARK,
  THEME_FIRST = THEME_LIGHT,
  THEME_LAST = THEME_DARK,
};
extern Theme_t APP_THEME;

extern GLclampf THEME_CLEARCOLOR_R;
extern GLclampf THEME_CLEARCOLOR_G;
extern GLclampf THEME_CLEARCOLOR_B;
extern GLclampf THEME_CLEARCOLOR_A;



const GLfloat DEFAULT_MOUSE_SENSITIVITY_MOVE = 0.08f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ROTATE = 0.4f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ZOOM = 0.01f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_MOVE = 0.1f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ROTATE = 2.5f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ZOOM = 0.01f;



enum Direction_t : char // uint8_t
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

const GLfloat DEFAULT_CAMERA_DISTANCE = 10.0f;
enum Camera_t : char // uint8_t
{
  CAMERA_FRONT = 0, // Camera at Z looking to center
  CAMERA_RIGHT = 1, // Camera at X looking to center
  CAMERA_BACK = 2,  // Camera at -Z looking to center
  CAMERA_LEFT = 3,  // Camera at -X looking to center

  CAMERA_TOP = 4,    // Camera at Y looking to center
  CAMERA_BOTTOM = 5, // Camera at -Y looking to center

  CAMERA_DIAGONAL = 6, // Camera between X, Y and Z looking to center
  CAMERA_LAST = CAMERA_DIAGONAL,

  DEFAULT_CAMERA = CAMERA_FRONT,
  CAMERA_NONE = 7,
};

enum ViewMode : char // uint8_t
{
  VIEWMODE_TEXTURE = 0,
  VIEWMODE_FLATSHADE = 1,
  VIEWMODE_WIREFRAME = 2,

  VIEWMODE_LAST = VIEWMODE_WIREFRAME,
  VIEWMODE_NONE = 3,
};
