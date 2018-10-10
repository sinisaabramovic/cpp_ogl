//
//  Light.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 11/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Light.hpp"



Light::~Light() { 
    
}

Light::Light() :
_colour(glm::vec3(1.0f, 1.0f, 1.0f)),
_ambientIntensity(1.0f),
_diffuseIntensity(0.0f)
{
    
}

Light::Light(const glm::vec3 &color,
             const GLfloat &ambientIntensity,
             const GLfloat &diffuseIntensity) :
_colour(color),
_ambientIntensity(ambientIntensity),
_diffuseIntensity(diffuseIntensity)
{
    
}

Light::Light(const GLfloat &red,
             const GLfloat &green,
             const GLfloat &blue,
             const GLfloat &aIntensity,
             const GLfloat &dIntensity)
{
    _colour = glm::vec3(red, green, blue);
    _ambientIntensity = aIntensity;
    _diffuseIntensity = dIntensity;
}









