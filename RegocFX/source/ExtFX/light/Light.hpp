//
//  Light.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 11/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Color.hpp"

class Light{
protected:
    
    glm::vec3 _colour;
    GLfloat _ambientIntensity;
    GLfloat _diffuseIntensity;
    
public:
    
    Light();
    
    Light(const glm::vec3 &color,
          const GLfloat& ambientIntensity,
          const GLfloat& diffuseIntensity);
    
    Light(const GLfloat& red,
          const GLfloat& green,
          const GLfloat& blue,
          const GLfloat& aIntensity,
          const GLfloat& dIntensity);
    
    ~Light();
    
};

#endif /* Light_hpp */
