//
//  DirectionalLight.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>
#include "Light.hpp"

class DirectionLight : public Light{
  
private:
    glm::vec3 _direction;

public:
    DirectionLight();
    ~DirectionLight();
    
    void UseLight(GLuint ambientIntensityLocation,
                  GLuint ambientColorLocation,
                  GLuint diffuseIntensityLocation,
                  GLuint directionLocation);
    
    DirectionLight(const GLfloat& red,
          const GLfloat& green,
          const GLfloat& blue,
          const GLfloat& aIntensity,
          const GLfloat& dIntensity,
          const GLfloat& xDir,
          const GLfloat& yDir,
          const GLfloat& zDir);
    
    DirectionLight(const glm::vec3 &color,
                   const GLfloat& ambientIntensity,
                   const glm::vec3& direction,
                   const GLfloat& diffuseIntensity);
};

#endif /* DirectionalLight_hpp */
