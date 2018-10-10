//
//  main.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 02/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Material.hpp"

#include "CommonValues.h"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "Model.hpp"

#include "CubeData.h"

#include "OpenGL_Error_Assert.hpp"


// Window dimensions
const GLint WIDTH = 1366, HEIGHT = 768;

GLfloat deltaTime = 0.0f;
GLfloat lasTime = 0.0f;

const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader *> shaderList;
Window* mainWindow = new Window(WIDTH, HEIGHT);
Camera* mainCamera;

Texture brickTexture;
Texture dirtTexture;

DirectionLight _mainDirectionalLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Material shinyMaterial;
Material dullMaterial;

// TODO THIS IS JUST FOR TEST
Model xWing;

// Vertex Shader code
static const char* vShader = "usr/resources/basicshader2.vert";

// Fragment Shader
static const char* fShader = "usr/resources/basicshader2.frag";

// TODO THIS IS JUST FOR TEST
static const char* testModelPath = "usr/resources/Models/test_model_2.obj";

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[] = {
    //   x       y       z      u     v           normals
        -1.0f, -1.0f,  -0.6f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
        0.0f,  -1.0f,  1.0f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
        1.0f,  -1.0f,  -0.6f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
        0.0f,   1.0f,  0.0f,    0.5f, 1.0f,   0.0f, 0.0f, 0.0f
    };
    
    unsigned int floorIndicies[] =
    {
        0, 2, 1,
        1, 2, 3
    };
    
    GLfloat floorVertices[] =
    {
        -10.0f, 0.0f, -10.0f,  0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f,   10.0f, 0.0f,     0.0f, -1.0f, 0.0f,
        -10, 0.0f, 10.0f,      0.0f, 10.0f,     0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f,    10.0f, 10.0f,    0.0f, -1.0f, 0.0f
    };
    
    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    
    Mesh *obj = new  Mesh();
    obj->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj);
    
    Mesh *obj2 = new  Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);
    
    Mesh *obj3 = new  Mesh();
    obj3->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj3);
    
    Mesh *floor = new  Mesh();
    floor->CreateMesh(floorVertices, floorIndicies, 32, 6);
    meshList.push_back(floor);
    
    Mesh *topFloor = new  Mesh();
    topFloor->CreateMesh(floorVertices, floorIndicies, 32, 6);
    meshList.push_back(topFloor);
}

void CreateShaders(){
    Shader *shader1 = new Shader();
    shader1->createShaderFromFile(vShader, fShader);
    shaderList.push_back(shader1);
}

int main()
{
    mainWindow->windowInitialise();
    
    CreateObjects();
    CreateShaders();
    
    // TODO THIS IS JUST FOR TEST
    //dumpModel.LoadModel(std::string(testModelPath));
    
    xWing = Model();
    xWing.LoadModel(std::string(testModelPath));
    
    brickTexture = Texture("usr/resources/Textures/brick.png");
    brickTexture.loadTextureA();
    dirtTexture = Texture("usr/resources/Textures/dirt.png");
    dirtTexture.loadTextureA();
    
    shinyMaterial = Material(4.0f, 128);
    dullMaterial = Material(0.3f, 4);
    
    _mainDirectionalLight = DirectionLight(1.0f, 1.0f, 1.0f,
                                           0.2f, 0.6f,
                                           0.0f, 0.0f, -1.0f);
    
    unsigned int pointLightCount = 0;
    
    pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
                                0.0f, 0.1f,
                                0.0f, 3.5f, 0.0f,
                                0.3f, 0.2f, 0.1f);
    
    
    pointLightCount++;
    
    pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
                                0.0f, 0.1f,
                                -4.0f, 2.0f, 0.0f,
                                0.3f, 0.1f, 0.1f);
    
    
    pointLightCount++;
    
    //pointLights[2] = PointLight(0.0f, 0.5f, 1.0f,
     //                           0.1f, 0.1f,
      //                          -4.0f, 0.0f, 0.0f,
        //                        0.3f, 0.2f, 0.1f);
    //pointLightCount++;
    
    unsigned int spotLightCount = 0;
    
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
                              0.0f, 2.0f,
                              0.0f, 0.0f, 0.0f,
                              0.0f, -1.0f, 0.0f,
                              1.0f, 0.0f, 0.0f,
                              20.0f);
    spotLightCount++;
    
    
    
    
    
    // Define of the main camera
    mainCamera = new Camera(glm::vec3(0.0f, 1.0f, -5.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f),
                            glm::radians(65.0f), 0.0f, 8.0f, 0.25f);
    
    GLuint uniProj = 0,
    uniModel = 0,
    uniView = 0,
    uniEyePosition = 0,
    uniShininess = 0,
    uniSpecularIntensity = 0;
    
    glm::mat4 projection = glm::perspective(glm::radians(65.0f),
                                            (GLfloat)mainWindow->getBufferWidth() / (GLfloat)mainWindow->getBufferHeight(),
                                            0.1f,
                                            100.0f);
    
    while (!mainWindow->getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lasTime;
        lasTime = now;
        
        // Get + Handle user input events
        glfwPollEvents();
        
        mainCamera->keyControll(mainWindow->getKeys(), deltaTime);
        mainCamera->mouseControll(mainWindow->getXChanged(), mainWindow->getYChanged(), true);
       
        // Clear window
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
        shaderList[0]->useShader();

        uniModel = shaderList[0]->getModelLocation();
        uniProj = shaderList[0]->getProjectionLocation();
        uniView = shaderList[0]->getViewLocation();
        uniEyePosition = shaderList[0]->getEyePosition();
        uniSpecularIntensity = shaderList[0]->getSpecularLocation();
        uniShininess = shaderList[0]->getShininessLocation();
        
        glm::vec3 lowerLight = mainCamera->getCameraPosition();
        lowerLight.y -= 0.5f;
        lowerLight.z += 1.0f;
       // spotLights[0].SetFlash(lowerLight, mainCamera->getCameraDirecion());
        
        
        shaderList[0]->setDirectionLight(&_mainDirectionalLight);
        shaderList[0]->setPointLights(pointLights, pointLightCount);
        //shaderList[0]->setSpotLights(spotLights, spotLightCount);
        
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(mainCamera->calculateViewMatrix()));
        glUniform3f(uniEyePosition,
                    mainCamera->getCameraPosition().x,
                    mainCamera->getCameraPosition().y,
                    mainCamera->getCameraPosition().z);
        
        glm::mat4 model = glm::mat4(1.0f);
        
        // Test meshes
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        brickTexture.useTexture();
        shinyMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        meshList[0]->RenderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTexture.useTexture();
        dullMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        meshList[1]->RenderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTexture.useTexture();
        dullMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        meshList[2]->RenderMesh();
        
        
        // FLOOR
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTexture.useTexture();
        shinyMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        meshList[3]->RenderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
       // model = glm::rotate(model, glm::radians(45), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        //dirtTexture.useTexture();
        shinyMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        xWing.RenderModel();
        
        
        // TOP FLOOR
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        brickTexture.useTexture();
        shinyMaterial.UseMaterial(uniSpecularIntensity, uniShininess);
        meshList[4]->RenderMesh();
        
        
        GLCall(glUseProgram(0));
        
        mainWindow->swapBuffers();
    }
    
    for(int i = 0; i < shaderList.size(); i++){
        delete shaderList[i];
    }
    
    shaderList.clear();
    
    for(int i = 0; i < meshList.size(); i++){
        delete meshList[i];
    }
    
    shaderList.clear();
    meshList.clear();
    delete mainCamera;
    delete mainWindow;
    
    glfwTerminate();
    
    printf("EOF Program \n");

    
    return 0;
}
