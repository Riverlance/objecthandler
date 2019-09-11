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

enum Theme_t : uint8_t
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



const GLfloat DEFAULT_CAMERA_DISTANCE = 10.0f;

const GLfloat PITCH_CONSTRAINT_RANGE = 0.001f;
const GLfloat PITCH_CONSTRAINT_TOP = 90.0f - PITCH_CONSTRAINT_RANGE;
const GLfloat PITCH_CONSTRAINT_BOTTOM = 270.0f + PITCH_CONSTRAINT_RANGE;

const GLfloat DEFAULT_YAW = 270.0f; // Rotation around y axis
const GLfloat DEFAULT_PITCH = 0.0f; // Rotation around x axis

const GLfloat DEFAULT_ZOOM = 45.0f; // Do not change this value!
const GLfloat ZOOM_MAX = 1.0f; // Max is close to 45.0f

const GLfloat DEFAULT_MOUSE_SENSITIVITY_MOVE = 0.07f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ROTATE = 0.4f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ZOOM = 0.02f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_MOVE = 0.01f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ROTATE = 0.1f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ZOOM = 0.001f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_MOVE = 0.01f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_ROTATE = 0.1f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_ZOOM = 0.001f;

// Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;



enum Direction_t : uint8_t
{
  DIRECTION_NONE = 0,

  DIRECTION_NORTH = 1 << 0,
  DIRECTION_EAST = 1 << 1,
  DIRECTION_SOUTH = 1 << 2,
  DIRECTION_WEST = 1 << 3,

  DIRECTION_LAST = DIRECTION_WEST,
};

enum Camera_t : uint8_t
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

enum Device_t : uint8_t
{
  DEVICE_NONE = 0,

  DEVICE_MOUSE = 1 << 0,
  DEVICE_KEYBOARD = 1 << 1,
  DEVICE_JOYSTICK = 1 << 2,

  DEVICE_LAST = DEVICE_JOYSTICK,
};

enum ViewMode : uint8_t
{
  VIEWMODE_TEXTURE = 0,
  VIEWMODE_FLATSHADE = 1,
  VIEWMODE_WIREFRAME = 2,

  VIEWMODE_LAST = VIEWMODE_WIREFRAME,
  VIEWMODE_NONE = 3,
};
