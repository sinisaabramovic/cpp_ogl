//
//  Shader.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 04/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <unistd.h>
#include "OpenGL_Error_Assert.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "CommonValues.h"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

class Shader{
private:
    GLuint _shaderProgamID,
    _uniformProjectionMatrixID,
    _uniormModelMatrixID,
    _uniformEyePosition,
    _uniformSpecularIntensity,
    _uniformMaterialShinniess;
    
    GLuint _uniformViewMatrixID;
    void _compileShader(const char* vertexShaderString, const char* fragmentShaderString);
    void _addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    std::string ReadFile(const char* fileLocation);
    
    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformDirection;
    } uniformDirectionLight;
    
    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];
    
    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
        GLuint uniformDirection;
        GLuint uniformEdge;
        
    } uniformSpotLight[MAX_SPOT_LIGHTS];
    
    GLuint uniformPointLightCount;
    GLuint uniformSpotLightCount;
    
    int pointLightCount;
    int spotLightCount;
public:
    
    Shader();
    ~Shader();
    
    void createShaderFromString(const char* vertexShaderString, const char* fragmentShaderString);
    void createShaderFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);
    void useShader();
    void clearShader();
    GLuint getProgramID();
    bool isProgramValid();
    
    GLuint getProjectionLocation();
    GLuint getModelLocation();
    GLuint getViewLocation();
    
    GLuint getAmbientIntensityLocation();
    GLuint getAmbientColorLocation();
    
    GLuint getDiffuseIntensityLocation();
    GLuint getDiffuseDirection();
    
    GLuint getSpecularLocation();
    GLuint getShininessLocation();
    
    GLuint getEyePosition();
    
    void setDirectionLight(DirectionLight * directionLight);
    void setPointLights(PointLight * pLight, unsigned int lightCount);
    void setSpotLights(SpotLight * spLight, unsigned int lightCount);
};

#endif /* Shader_hpp */
