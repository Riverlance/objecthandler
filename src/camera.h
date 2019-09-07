/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include "objecthandlerpch.h"

#include <SDL.h>
#include <GL/glew.h>
#include "const.h"

const GLfloat PITCH_CONSTRAINT_RANGE = 0.001f;
const GLfloat PITCH_CONSTRAINT_TOP = 90.0f - PITCH_CONSTRAINT_RANGE;
const GLfloat PITCH_CONSTRAINT_BOTTOM = 270.0f + PITCH_CONSTRAINT_RANGE;

const GLfloat DEFAULT_ZOOM = 45.0f;



class Camera
{
  public:
    // Initialize
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = DEFAULT_YAW, GLfloat pitch = DEFAULT_PITCH);
    Camera(GLfloat positionX, GLfloat positionY, GLfloat positionZ, GLfloat upCoordinateX, GLfloat upCoordinateY, GLfloat upCoordinateZ, GLfloat yaw = DEFAULT_YAW, GLfloat pitch = DEFAULT_PITCH);

    // Deallocate memory
    ~Camera() {};

    // Prevent clone this object
    Camera(const Camera&) = delete; // Prevent construction by copying
    Camera& operator=(const Camera&) = delete; // Prevent assignment



    bool init() {};
    bool onInit() {};



    // Starting where to be looking at: looking front at the position based on worldUp
    glm::mat4 getViewMatrix() { return glm::lookAt(position, position + front, worldUp); }

    GLfloat getZoomSize() { return zoomSize; }

    void move(Direction_t direction, GLfloat speed = (GLfloat)1.0f);
    void rotate(Direction_t direction, GLfloat speed = (GLfloat)1.0f, GLboolean constrainPitch = true);
    void zoom(Direction_t direction, GLfloat speed = (GLfloat)1.0f);




  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat zoomSize;



    void updateCameraVectors();
    bool upsideDown = false;
    void upsideDownCamera();
};
