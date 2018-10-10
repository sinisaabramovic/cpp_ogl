//
//  Texture.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 07/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <unistd.h>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include "stb_image.h"

class Texture{
private:
    GLuint textureID;
    int width, height, bitDepth;
    const char* fileLocation;
public:
    Texture();
    Texture(const char* fileLoc);
    ~Texture();
    
    bool loadTexture();
    bool loadTextureA();
    
    void useTexture();
    void clearTexture();
 
};

#endif /* Texture_hpp */
