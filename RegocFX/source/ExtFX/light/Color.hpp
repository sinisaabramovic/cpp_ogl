//
//  Color.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 11/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Color{
private:
    GLfloat red, green, blue;
public:
    Color();
    Color(const GLfloat& pRed, const GLfloat& pGreen, const GLfloat& blue);
    GLfloat getRed() const;
    GLfloat getGreen() const;
    GLfloat getBlue() const;
    void setRed(const GLfloat& red);
    void setGreen(const GLfloat& green);
    void setBlue(const GLfloat& blue);
    ~Color();
};

#endif /* Color_hpp */
