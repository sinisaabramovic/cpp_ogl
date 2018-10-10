//
//  PointLight.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>
#include "Light.hpp"

class PointLight : public Light{
protected:
    glm::vec3 _position;
    
    GLfloat _constant, _linear, _exponent;
    
public:
    PointLight();
    ~PointLight();
    
    PointLight(const GLfloat& red,
               const GLfloat& green,
               const GLfloat& blue,
               const GLfloat& aIntensity,
               const GLfloat& dIntensity,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat constant,
               GLfloat linear,
               GLfloat exponent);
    
    void UseLight(GLuint ambientIntensityLocation,
                  GLuint ambientColorLocation,
                  GLuint diffuseIntensityLocation,
                  GLuint positionLocation,
                  GLuint constantLocation,
                  GLuint linearLocation,
                  GLuint exponentLocation);
};

#endif /* PointLight_hpp */
