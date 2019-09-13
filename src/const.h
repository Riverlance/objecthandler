/**
 * Object Handler - A 3D Model Viewer.
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



const GLfloat DEFAULT_CAMERA_DISTANCE = 10.0f;

const GLfloat PITCH_CONSTRAINT_RANGE = 0.001f;
const GLfloat PITCH_CONSTRAINT_TOP = 90.0f - PITCH_CONSTRAINT_RANGE;
const GLfloat PITCH_CONSTRAINT_BOTTOM = 270.0f + PITCH_CONSTRAINT_RANGE;

const GLfloat DEFAULT_YAW = 270.0f; // Rotation around y axis
const GLfloat DEFAULT_PITCH = 0.0f; // Rotation around x axis

const GLfloat DEFAULT_ZOOM = 45.0f; // Do not change this value!
const GLfloat ZOOM_MAX = 1.0f; // Max is close to 45.0f

const GLfloat DEFAULT_MOUSE_SENSITIVITY_MOVE = 70.0f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ROTATE = 400.0f;
const GLfloat DEFAULT_MOUSE_SENSITIVITY_ZOOM = 20.0f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_MOVE = 10.0f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ROTATE = 100.0f;
const GLfloat DEFAULT_KEYBOARD_SENSITIVITY_ZOOM = 1.0f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_MOVE = 10.0f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_ROTATE = 100.0f;
const GLfloat DEFAULT_JOYSTICK_SENSITIVITY_ZOOM = 1.0f;

const GLfloat MAX_MOUSE_SENSITIVITY_MOVE = 10000.0f;
const GLfloat MAX_MOUSE_SENSITIVITY_ROTATE = 1000.0f;
const GLfloat MAX_MOUSE_SENSITIVITY_ZOOM = 25.0f;
const GLfloat MAX_KEYBOARD_SENSITIVITY_MOVE = 10000.0f;
const GLfloat MAX_KEYBOARD_SENSITIVITY_ROTATE = 1000.0f;
const GLfloat MAX_KEYBOARD_SENSITIVITY_ZOOM = 25.0f;
const GLfloat MAX_JOYSTICK_SENSITIVITY_MOVE = 10000.0f;
const GLfloat MAX_JOYSTICK_SENSITIVITY_ROTATE = 1000.0f;
const GLfloat MAX_JOYSTICK_SENSITIVITY_ZOOM = 25.0f;

const GLfloat ADD_MOUSE_SENSITIVITY_MOVE = 10.0f;
const GLfloat ADD_MOUSE_SENSITIVITY_ROTATE = 1.0f;
const GLfloat ADD_MOUSE_SENSITIVITY_ZOOM = 0.1f;
const GLfloat ADD_KEYBOARD_SENSITIVITY_MOVE = 10.0f;
const GLfloat ADD_KEYBOARD_SENSITIVITY_ROTATE = 1.0f;
const GLfloat ADD_KEYBOARD_SENSITIVITY_ZOOM = 0.1f;
const GLfloat ADD_JOYSTICK_SENSITIVITY_MOVE = 10.0f;
const GLfloat ADD_JOYSTICK_SENSITIVITY_ROTATE = 1.0f;
const GLfloat ADD_JOYSTICK_SENSITIVITY_ZOOM = 0.1f;

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
  CAMERA_NONE = CAMERA_LAST + 1,
};

enum Device_t : uint16_t
{
  DEVICE_NONE = 0,

  DEVICE_MOUSE = 1 << 0,
  DEVICE_KEYBOARD = 1 << 1,
  DEVICE_JOYSTICK = 1 << 2,

  DEVICE_LAST = DEVICE_JOYSTICK,
};

enum ViewMode_t : uint16_t
{
  VIEWMODE_FILL = 0,
  VIEWMODE_LINE = 1,
  VIEWMODE_GL_POINT = 2,
  VIEWMODE_LAST = VIEWMODE_GL_POINT,

  DEFAULT_VIEWMODE = VIEWMODE_FILL,
  VIEWMODE_NONE = VIEWMODE_LAST + 1,
};

enum Theme_t : uint8_t
{
  THEME_LIGHT = 0,
  THEME_DARK = 1,
  THEME_LAST = THEME_DARK,

  DEFAULT_THEME = THEME_DARK,
  THEME_NONE = THEME_LAST + 1,
};
extern Theme_t APP_THEME;
extern GLclampf THEME_CLEARCOLOR_R;
extern GLclampf THEME_CLEARCOLOR_G;
extern GLclampf THEME_CLEARCOLOR_B;
extern GLclampf THEME_CLEARCOLOR_A;



struct Vertex
{
  // Position
  glm::vec3 Position;

  // Normal
  glm::vec3 Normal;

  // Texture Coordinates
  glm::vec2 TextureCoordinates;
};

struct Texture
{
  GLuint id;
  std::string type;
  aiString path;
};
