//
//  Material.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 13/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Material.hpp"


Material::~Material()
{
  
}


Material::Material(GLfloat sIntensity, GLfloat sShininess) :
_specularIntensity(sIntensity), _shininess(sShininess)
{
    
}


Material::Material() :
_specularIntensity(0.0f), _shininess(0.0f)
{
  
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shinniessLocation) { 
    glUniform1f(specularIntensityLocation, _specularIntensity);
    glUniform1f(shinniessLocation, _shininess);
}

