//
//  Texture.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 07/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Texture.hpp"


void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}


void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


bool Texture::loadTextureA() {
    
    std::string pathLocation(fileLocation);
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    //std::cout << "Current Path: " << path << std::endl;
    std::string str_path(path);
    std::string str_location(fileLocation);
    pathLocation = str_path + std::string("/") + str_location;
#endif
    //std::cout << "Current Path: " << pathLocation << std::endl;
    
    unsigned char *texData = stbi_load(pathLocation.c_str(), &width, &height, &bitDepth, 0);
    if(!texData){
        printf("Failed to find: %s\n", fileLocation);
        return false;
    }
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
    
    return true;
}


Texture::Texture(const char *fileLoc) :
textureID(0), width(0), height(0), bitDepth(0)
{
    fileLocation = fileLoc;
}


Texture::Texture() :
textureID(0), width(0), height(0), bitDepth(0), fileLocation(nullptr)
{
    
}

Texture::~Texture() {
    clearTexture();
}

bool Texture::loadTexture() {
    std::string pathLocation(fileLocation);
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    //std::cout << "Current Path: " << path << std::endl;
    std::string str_path(path);
    std::string str_location(fileLocation);
    pathLocation = str_path + std::string("/") + str_location;
#endif
    //std::cout << "Current Path: " << pathLocation << std::endl;
    
    unsigned char *texData = stbi_load(pathLocation.c_str(), &width, &height, &bitDepth, 0);
    if(!texData){
        printf("Failed to find: %s\n", fileLocation);
        return false;
    }
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
    
    return true;
}


