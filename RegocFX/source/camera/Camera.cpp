//
//  Camera.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 05/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() :
position(glm::vec3(0.0f, 0.0f, 0.0f)),
worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
yaw(YAW),
pitch(PITCH),
Zoom(ZOOM),
front(glm::vec3(0.0f, 0.0f,-1.0f)),
movementSpeed(SPEED),
turnSpeed(SENSITIVITY),
firstMouse(true)
{
    update();
}

Camera::Camera(glm::vec3 startPosition,
               glm::vec3 startUp,
               GLfloat startYaw,
               GLfloat startPitch,
               GLfloat startSpeed,
               GLfloat startTurnSpeed) :
position(startPosition),
worldUp(startUp),
yaw(startYaw),
pitch(startPitch),
front(glm::vec3(0.0f, 0.0f,-1.0f)),
movementSpeed(startSpeed),
turnSpeed(startTurnSpeed),
firstMouse(true)
{
    update();
}

void Camera::update() {
    
    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(_front);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
    
}

void Camera::keyControll(bool *keys, GLfloat deltaTime)
{
    GLfloat velocity = movementSpeed * deltaTime;
    // If I dont wont to move or better say fly up :D
    front.y = sin(glm::radians(0.0f));
    if(keys[GLFW_KEY_W]){
        position += front * velocity;
    }
    
    if(keys[GLFW_KEY_S]){
        position -= front * velocity;
    }
    
    if(keys[GLFW_KEY_A]){
        //position -= right * (velocity);
        position -= glm::normalize(glm::cross(front, up)) * velocity;
    }
    
    if(keys[GLFW_KEY_D]){
        //position += right * (velocity);
        position += glm::normalize(glm::cross(front, up)) * velocity;
    }
    update();
}

glm::mat4 Camera::calculateViewMatrix() { 
    return glm::lookAt(position, position + front, up);
}

void Camera::mouseControll(GLfloat xChange, GLfloat yChange, GLboolean constrainPitch = true) {
    
    xChange *= turnSpeed;
    yChange *= turnSpeed;
    
    yaw += xChange;
    pitch += yChange;
    
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch){
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    update();
}

Camera::~Camera() { 
    
}

glm::vec3 Camera::getCameraPosition() { 
    return position;
}

glm::vec3 Camera::getCameraDirecion() { 
    return glm::normalize(front);
}










