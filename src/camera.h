/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include "objecthandlerpch.h"

#include <SDL.h>
#include <GL/glew.h>
#include "const.h"



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

    glm::vec3 getPosition() { return position; }
    glm::vec3 getFrontVector() { return front; }
    GLfloat getZoomSize() { return zoomSize; }

    void move(Direction_t direction, GLfloat speed = (GLfloat)1.0f);
    void rotate(Direction_t direction, GLfloat speed = (GLfloat)1.0f, GLboolean constrainPitch = true);
    void zoom(Direction_t direction, GLfloat speed = (GLfloat)1.0f);

    // Switch camera position and direction
    void updateCamera(Camera_t cameraType, GLfloat distance = (GLfloat)0.0f);




  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat zoomSize;

    Camera_t lastCameraType;



    void updateCameraVectors();
    bool upsideDown = false;
    void upsideDownCamera();
};
