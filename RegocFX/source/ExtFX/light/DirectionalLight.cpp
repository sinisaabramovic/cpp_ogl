//
//  DirectionalLight.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "DirectionalLight.hpp"


DirectionLight::~DirectionLight() { 
    
}

DirectionLight::DirectionLight(const glm::vec3 &color, const GLfloat &ambientIntensity, const glm::vec3 &direction, const GLfloat &diffuseIntensity)
{
    _colour = color;
    _ambientIntensity = ambientIntensity;
    _direction = direction;
    _diffuseIntensity = diffuseIntensity;
}


DirectionLight::DirectionLight() : Light()
{
    _direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionLight::DirectionLight(const GLfloat &red,
                               const GLfloat &green,
                               const GLfloat &blue,
                               const GLfloat &aIntensity,
                               const GLfloat &dIntensity,
                               const GLfloat &xDir,
                               const GLfloat &yDir,
                               const GLfloat &zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
    _direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionLight::UseLight(GLuint ambientIntensityLocation,
                     GLuint ambientColorLocation,
                     GLuint diffuseIntensityLocation,
                     GLuint directionLocation)
{
    
    /*
    _mainDirectionalLight = DirectionLight(1.0f, 1.0f, 1.0f,
                                           0.3f, 0.6f,
                                           0.0f, 0.0f, -1.0f);
    */
    glUniform3f(ambientColorLocation, _colour.x, _colour.y, _colour.z);
    glUniform1f(ambientIntensityLocation, _ambientIntensity);
    
    glUniform3f(directionLocation, _direction.x, _direction.y, _direction.z);
    glUniform1f(diffuseIntensityLocation, _diffuseIntensity);
}






