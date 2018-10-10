//
//  SpotLight.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 14/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include "PointLight.hpp"

class SpotLight : public PointLight {
  
private:
    glm::vec3 _direction;
    
    GLfloat _edge, _processEdge;
public:
    
    SpotLight();
    
    SpotLight(const GLfloat& red,
               const GLfloat& green,
               const GLfloat& blue,
               const GLfloat& aIntensity,
               const GLfloat& dIntensity,
               GLfloat xPos,
               GLfloat yPos,
               GLfloat zPos,
               GLfloat xDir, GLfloat yDir, GLfloat zDir,
               GLfloat constant,
               GLfloat linear,
               GLfloat exponent,
               GLfloat edge);
    
    void UseLight(GLuint ambientIntensityLocation,
                  GLuint ambientColorLocation,
                  GLuint diffuseIntensityLocation,
                  GLuint positionLocation,
                  GLuint directionLocation,
                  GLuint constantLocation,
                  GLuint linearLocation,
                  GLuint exponentLocation,
                  GLuint edgeLocation);
    
    void SetFlash(glm::vec3 pos, glm::vec3 dir);
    
    ~SpotLight();
    
};

#endif /* SpotLight_hpp */
