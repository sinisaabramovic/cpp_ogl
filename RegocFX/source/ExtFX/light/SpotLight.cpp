//
//  SpotLight.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "SpotLight.hpp"


SpotLight::~SpotLight()  {
 
}


SpotLight::SpotLight() : PointLight()
{
    _direction = glm::vec3(0.0f, -1.0f, 0.0f);
    _edge = 0.0f;
    _processEdge = cosf(glm::radians(_edge));
}

SpotLight::SpotLight(const GLfloat &red,
                     const GLfloat &green,
                     const GLfloat &blue,
                     const GLfloat &aIntensity,
                     const GLfloat &dIntensity,
                     GLfloat xPos,
                     GLfloat yPos,
                     GLfloat zPos,
                     GLfloat xDir,
                     GLfloat yDir,
                     GLfloat zDir,
                     GLfloat constant,
                     GLfloat linear,
                     GLfloat exponent,
                     GLfloat edge) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, constant, linear, exponent)
{
    _direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    _edge = edge;
    _processEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLocation,
                         GLuint ambientColorLocation,
                         GLuint diffuseIntensityLocation,
                         GLuint positionLocation,
                         GLuint directionLocation,
                         GLuint constantLocation,
                         GLuint linearLocation,
                         GLuint exponentLocation,
                         GLuint edgeLocation)
{
    glUniform3f(ambientColorLocation, _colour.x, _colour.y, _colour.z);
    glUniform1f(ambientIntensityLocation, _ambientIntensity);
    glUniform1f(diffuseIntensityLocation, _diffuseIntensity);
    
    glUniform3f(positionLocation, _position.x, _position.y, _position.z);
    glUniform1f(constantLocation, _constant);
    glUniform1f(linearLocation, _linear);
    glUniform1f(exponentLocation, _exponent);
    
    glUniform3f(directionLocation, _direction.x, _direction.y, _direction.z);
    glUniform1f(edgeLocation, _processEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir) { 
    _position = pos;
    _direction = dir;
}





