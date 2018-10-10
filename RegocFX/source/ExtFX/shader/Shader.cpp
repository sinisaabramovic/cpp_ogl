//
//  Shader.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 04/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Shader.hpp"


Shader::~Shader() { 
    clearShader();
}


Shader::Shader() :
_shaderProgamID(0), _uniformProjectionMatrixID(0), _uniormModelMatrixID(0), pointLightCount(0), spotLightCount(0)
{
    
}

void Shader::clearShader() {
    if(_shaderProgamID != 0){
        GLCall(glDeleteProgram(_shaderProgamID));
        _shaderProgamID = 0;
    }
    _uniformProjectionMatrixID = 0;
    _uniormModelMatrixID = 0;
}


void Shader::useShader() { 
    glUseProgram(_shaderProgamID);
}


void Shader::createShaderFromString(const char *vertexShaderString, const char *fragmentShaderString) {
    _compileShader(vertexShaderString, fragmentShaderString);
}


void Shader::_addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType) {
    
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    
    GLCall(glShaderSource(theShader, 1, theCode, codeLength));
    GLCall(glCompileShader(theShader));
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    GLCall(glGetShaderiv(theShader, GL_COMPILE_STATUS, &result));
    if (!result)
    {
        GLCall(glGetShaderInfoLog(theShader, 1024, NULL, eLog));
        fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }
    
    GLCall(glAttachShader(theProgram, theShader));
    
}


void Shader::_compileShader(const char *vertexShaderString, const char *fragmentShaderString) {
    
    GLCall(_shaderProgamID = glCreateProgram());
    
    if (!_shaderProgamID)
    {
        printf("Failed to create shader\n");
        return;
    }
    
    _addShader(_shaderProgamID, vertexShaderString, GL_VERTEX_SHADER);
    _addShader(_shaderProgamID, fragmentShaderString, GL_FRAGMENT_SHADER);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    GLCall(glLinkProgram(_shaderProgamID));
    GLCall(glGetProgramiv(_shaderProgamID, GL_LINK_STATUS, &result));
    if (!result)
    {
        glGetProgramInfoLog(_shaderProgamID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }
    
    GLCall(_uniormModelMatrixID = glGetUniformLocation(_shaderProgamID, "model"));
    GLCall(_uniformProjectionMatrixID = glGetUniformLocation(_shaderProgamID, "proj"));
    GLCall(_uniformViewMatrixID = glGetUniformLocation(_shaderProgamID, "view"));
    GLCall(uniformDirectionLight.uniformColor = glGetUniformLocation(_shaderProgamID, "directionLight.base.color"));
    GLCall(uniformDirectionLight.uniformAmbientIntensity = glGetUniformLocation(_shaderProgamID, "directionLight.base.ambientIntensity"));
    // Diffuse prop
    GLCall(uniformDirectionLight.uniformDiffuseIntensity = glGetUniformLocation(_shaderProgamID, "directionLight.base.diffuseIntensity"));
    GLCall(uniformDirectionLight.uniformDirection= glGetUniformLocation(_shaderProgamID, "directionLight.direction"));
    // Specular prop
    GLCall(_uniformSpecularIntensity = glGetUniformLocation(_shaderProgamID, "material.specularIntensity"));
    GLCall(_uniformMaterialShinniess = glGetUniformLocation(_shaderProgamID, "material.shininess"));
    GLCall(_uniformEyePosition = glGetUniformLocation(_shaderProgamID, "eyePosition"));
    
    uniformPointLightCount = glGetUniformLocation(_shaderProgamID, "pointLightCount");
    
    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char locationBuffer[100] = {'\0'};
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].base.color", i);
        uniformPointLight[i].uniformColor = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(_shaderProgamID, locationBuffer);
    }
    
    uniformSpotLightCount = glGetUniformLocation(_shaderProgamID, "spotLightCount");
    
    for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        char locationBuffer[100] = {'\0'};
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.base.color", i);
        uniformSpotLight[i].uniformColor = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.base.ambientIntensity", i);
        uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.base.diffuseIntensity", i);
        uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.position", i);
        uniformSpotLight[i].uniformPosition = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.constant", i);
        uniformSpotLight[i].uniformConstant = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.linear", i);
        uniformSpotLight[i].uniformLinear = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].base.exponent", i);
        uniformSpotLight[i].uniformExponent = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].direction", i);
        uniformSpotLight[i].uniformDirection = glGetUniformLocation(_shaderProgamID, locationBuffer);
        
        snprintf(locationBuffer, sizeof(locationBuffer), "spotLights[%d].edge", i);
        uniformSpotLight[i].uniformEdge = glGetUniformLocation(_shaderProgamID, locationBuffer);
    }
}

GLuint Shader::getModelLocation() {
    return _uniormModelMatrixID;
}

GLuint Shader::getProjectionLocation() { 
    return _uniformProjectionMatrixID;
}

void Shader::createShaderFromFile(const char *vertexShaderPath, const char *fragmentShaderPath) { 
    std::string vertexString = ReadFile(vertexShaderPath);
    std::string fragmentString = ReadFile(fragmentShaderPath);
    
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();
    
    _compileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char *fileLocation) { 
    std::string content;
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
    
    std::ifstream fileStream(pathLocation.c_str(), std::ios::in);
    
    if(!fileStream.is_open()){
        std::cout << strerror(errno) << '\n';
        std::cout << "Fail to read " << fileLocation << std::endl;
        return "";
    }
    
    std::string line = "";
    
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    
    fileStream.close();
    
    return content;
}

GLuint Shader::getProgramID() { 
    return _shaderProgamID;
}

bool Shader::isProgramValid() {
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glValidateProgram(_shaderProgamID);
    glGetProgramiv(_shaderProgamID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(_shaderProgamID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return false;
    }else{
        return true;
    }
}

GLuint Shader::getViewLocation() { 
    return _uniformViewMatrixID;
}

GLuint Shader::getAmbientColorLocation() { 
    return uniformDirectionLight.uniformColor;
}


GLuint Shader::getAmbientIntensityLocation() { 
    return uniformDirectionLight.uniformAmbientIntensity;
}

GLuint Shader::getDiffuseDirection() { 
    return uniformDirectionLight.uniformDirection;
}


GLuint Shader::getDiffuseIntensityLocation() { 
    return uniformDirectionLight.uniformDiffuseIntensity;
}

GLuint Shader::getShininessLocation() { 
    return _uniformMaterialShinniess;
}


GLuint Shader::getSpecularLocation() { 
    return _uniformSpecularIntensity;
}

GLuint Shader::getEyePosition() { 
    return _uniformEyePosition;
}

void Shader::setDirectionLight(DirectionLight *directionLight)
{
    directionLight->UseLight(uniformDirectionLight.uniformAmbientIntensity, uniformDirectionLight.uniformColor, uniformDirectionLight.uniformDiffuseIntensity, uniformDirectionLight.uniformDirection);
}

void Shader::setPointLights(PointLight *pLight, unsigned int lightCount)
{
    if(lightCount > MAX_POINT_LIGHTS){
        lightCount = MAX_POINT_LIGHTS;
    }
    
    glUniform1i(uniformPointLightCount, lightCount);
    
    for (size_t i = 0; i < lightCount; i++) {
        pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity,
                           uniformPointLight[i].uniformColor,
                           uniformPointLight[i].uniformDiffuseIntensity,
                           uniformPointLight[i].uniformPosition,
                           uniformPointLight[i].uniformConstant,
                           uniformPointLight[i].uniformLinear,
                           uniformPointLight[i].uniformExponent);
    }
}

void Shader::setSpotLights(SpotLight *spLight, unsigned int lightCount) { 
    if(lightCount > MAX_SPOT_LIGHTS){
        lightCount = MAX_SPOT_LIGHTS;
    }
    
    glUniform1i(uniformSpotLightCount, lightCount);
    
    for (size_t i = 0; i < lightCount; i++) {
        spLight[i].UseLight(uniformSpotLight[i].uniformAmbientIntensity,
                            uniformSpotLight[i].uniformColor,
                            uniformSpotLight[i].uniformDiffuseIntensity,
                            uniformSpotLight[i].uniformPosition,
                            uniformSpotLight[i].uniformDirection,
                            uniformSpotLight[i].uniformConstant,
                            uniformSpotLight[i].uniformLinear,
                            uniformSpotLight[i].uniformExponent,
                            uniformSpotLight[i].uniformEdge);
    }
}















