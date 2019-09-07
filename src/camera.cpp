/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "camera.h"



Camera::Camera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3 up /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, GLfloat yaw /*= DEFAULT_YAW*/, GLfloat pitch /*= DEFAULT_PITCH*/) :
  front(glm::vec3(0.0f, 0.0f, -1.0f)),
  zoomSize(DEFAULT_ZOOM)
{
  this->position = position;
  this->worldUp = up;

  this->yaw = yaw;
  this->pitch = pitch;

  updateCameraVectors();
};

Camera::Camera(GLfloat positionX, GLfloat positionY, GLfloat positionZ, GLfloat upCoordinateX, GLfloat upCoordinateY, GLfloat upCoordinateZ, GLfloat yaw /*= DEFAULT_YAW*/, GLfloat pitch /*= DEFAULT_PITCH*/) :
  front(glm::vec3(0.0f, 0.0f, -1.0f)),
  zoomSize(DEFAULT_ZOOM)
{
  this->position = glm::vec3(positionX, positionY, positionZ);
  this->worldUp = glm::vec3(upCoordinateX, upCoordinateY, upCoordinateZ);

  this->yaw = yaw;
  this->pitch = pitch;

  updateCameraVectors();
};



void Camera::move(Direction_t direction, GLfloat speed /*= (GLfloat)1.0f*/)
{
  if (direction == DIRECTION_NORTH)
    position += front * speed;

  if (direction == DIRECTION_EAST)
    position += right * speed;

  if (direction == DIRECTION_SOUTH)
    position -= front * speed;

  if (direction == DIRECTION_WEST)
    position -= right * speed;
};

void Camera::rotate(Direction_t direction, GLfloat speed /*= (GLfloat)1.0f*/, GLboolean constrainPitch /*= true*/)
{
  if (direction == DIRECTION_NORTH)
    pitch += speed; // around x
  else if (direction == DIRECTION_SOUTH)
    pitch -= speed; // around x

  if (direction == DIRECTION_WEST)
    yaw -= speed; // around y
  else if (direction == DIRECTION_EAST)
    yaw += speed; // around y
  
  // Reset variable (limit between angle 0 and 360; there is no negative values after this part)
  // Yaw
  if (yaw < 0.0f)
    yaw = 360.0f + std::ceil((float)yaw);
  else if (yaw > 360.0f)
    yaw = fmod(yaw, 360.0f); // yaw % 360
  // Pitch
  if (pitch < 0.0f)
    pitch = 360.0f + std::ceil((float)pitch);
  else if (pitch > 360.0f)
    pitch = fmod(pitch, 360.0f); // pitch % 360

  // Prevent from being able to out of bands on the screens and get flipped
  // - It prevents issues like gimbal lock
  // - Also prevents upsideDown camera ('roll' in z axis with 180 degrees), but limits pitch range to 180 degrees: pitch >= 0 && pitch < 90 || pitch > 270 && pitch < 360
  if (constrainPitch)
  {
    if (pitch > PITCH_CONSTRAINT_TOP && pitch < 270.0f && direction == DIRECTION_NORTH)
      pitch = PITCH_CONSTRAINT_TOP;
    else if (pitch < PITCH_CONSTRAINT_BOTTOM && pitch > 90.0f && direction == DIRECTION_SOUTH)
      pitch = PITCH_CONSTRAINT_BOTTOM;
  }
  // Fix upside down in pitch >= 0 && pitch <= 90 || pitch >= 270 && pitch < 360
  else
  {
    // Is in upside down range
    if (pitch >= 90.0f && pitch <= 270.0f)
    {
      if (!upsideDown) // this
      {
        upsideDown = true;
        upsideDownCamera();
      }
    }
    else
    {
      if (upsideDown) // this
      {
        upsideDown = false;
        upsideDownCamera();
      }
    }
  }

  updateCameraVectors();
};

void Camera::zoom(Direction_t direction, GLfloat speed /*= (GLfloat)1.0f*/)
{
  if (direction == DIRECTION_NORTH || direction == DIRECTION_EAST)
    zoomSize -= speed;

  if (direction == DIRECTION_SOUTH || direction == DIRECTION_WEST)
    zoomSize += speed;

  zoomSize = std::max(1.0f, std::min(zoomSize, 45.0f));
};



void Camera::updateCameraVectors()
{
  glm::vec3 _front;
  _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  _front.y = sin(glm::radians(pitch));
  _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  this->front = glm::normalize(_front);

  this->right = glm::normalize(glm::cross(this->front, this->worldUp));

  this->up = glm::normalize(glm::cross(this->right, this->front));
};

void Camera::upsideDownCamera()
{
  worldUp *= -1.0f;
  right *= -1.0f;
}
