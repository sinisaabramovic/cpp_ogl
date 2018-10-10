//
//  PointLight.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "PointLight.hpp"


PointLight::~PointLight()
{
    
}


PointLight::PointLight() : Light()
{
    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _constant = 1.0f;
    _linear = 0.0f;
    _exponent = 0.0f;
}

PointLight::PointLight(const GLfloat &red,
                       const GLfloat &green,
                       const GLfloat &blue,
                       const GLfloat &aIntensity,
                       const GLfloat &dIntensity,
                       GLfloat xPos, GLfloat yPos, GLfloat zPos,
                       GLfloat constant,
                       GLfloat linear,
                       GLfloat exponent) : Light(red, green, blue, aIntensity, dIntensity)
{
    _position = glm::vec3(xPos, yPos, zPos);
    _constant = constant;
    _linear = linear;
    _exponent = exponent;
}


void PointLight::UseLight(GLuint ambientIntensityLocation,
                          GLuint ambientColorLocation,
                          GLuint diffuseIntensityLocation,
                          GLuint positionLocation,
                          GLuint constantLocation,
                          GLuint linearLocation,
                          GLuint exponentLocation)
{
    
    glUniform3f(ambientColorLocation, _colour.x, _colour.y, _colour.z);
    glUniform1f(ambientIntensityLocation, _ambientIntensity);
    glUniform1f(diffuseIntensityLocation, _diffuseIntensity);
    
    glUniform3f(positionLocation, _position.x, _position.y, _position.z);
    glUniform1f(constantLocation, _constant);
    glUniform1f(linearLocation, _linear);
    glUniform1f(exponentLocation, _exponent);
    
}


