//
//  Material.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 13/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <GL/glew.h>

class Material{
private:
    
    GLfloat _specularIntensity;
    GLfloat _shininess;
    
public:
    
    Material();
    Material(GLfloat sIntensity, GLfloat sShininess);
    ~Material();
    
    void UseMaterial(GLuint specularIntensityLocation, GLuint shinniessLocation);
};

#endif /* Material_hpp */
