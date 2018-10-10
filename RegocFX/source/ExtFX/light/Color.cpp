//
//  Color.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 11/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Color.hpp"

Color::Color(const GLfloat &pRed, const GLfloat &pGreen, const GLfloat &pBlue)
{
    this->setRed(pRed);
    this->setGreen(pGreen);
    this->setBlue(pBlue);
}


Color::Color() :
red(0.0f), green(0.0f), blue(0.0f)
{
    
}

void Color::setBlue(const GLfloat &blue) {
    GLfloat value = blue;
    if(value > 1.0f){
        value = 1.0f;
    }
    if (value < 0.0f) {
        value = 0.0f;
    }
    
    //blue = value;
}


void Color::setGreen(const GLfloat &green) {
    GLfloat value = blue;
    if(value > 1.0f){
        value = 1.0f;
    }
    if (value < 0.0f) {
        value = 0.0f;
    }
    
    //green = value;
}


void Color::setRed(const GLfloat &red) {
    GLfloat value = blue;
    if(value > 1.0f){
        value = 1.0f;
    }
    if (value < 0.0f) {
        value = 0.0f;
    }
    
    //red = value;
}

GLfloat Color::getBlue() const {
    return blue;
}


GLfloat Color::getGreen() const {
    return green;
}


GLfloat Color::getRed() const {
    return red;
}

