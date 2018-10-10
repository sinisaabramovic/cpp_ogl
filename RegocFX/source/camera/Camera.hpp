//
//  Camera.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 05/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera{
private:
    
    GLfloat lastX;
    GLfloat lastY;
    
    bool firstMouse;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // for left and right
    GLfloat yaw;
    // up and down
    GLfloat pitch;
    
    GLfloat movementSpeed;
    float MouseSensitivity;
    GLfloat turnSpeed;
    GLfloat Zoom;
    
    void update();
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startSpeed, GLfloat startTurnSpeed);
    glm::mat4 calculateViewMatrix();
    void keyControll(bool *keys, GLfloat deltaTime);
    void mouseControll(GLfloat xChange, GLfloat yChange, GLboolean constrainPitch);
    
    glm::vec3 getCameraDirecion();
    
    glm::vec3 getCameraPosition();
    
    ~Camera();
};

#endif /* Camera_hpp */
