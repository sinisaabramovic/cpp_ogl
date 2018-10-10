//
//  Window.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 04/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Window.hpp"


Window::Window(const GLint &windowWidth, const GLint &windowHeight) :
width(windowWidth), height(windowHeight), mouseFirstMoved(true)
{
    xChange = 0.0f;
    yChange = 0.0f;
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
}


Window::Window() :
width(WND_CONST_WIDTH), height(WND_CONST_HEIGHT), mouseFirstMoved(true)
{
    xChange = 0.0f;
    yChange = 0.0f;
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
}

int Window::windowInitialise() { 
    // Initialise GLFW
    if (!glfwInit())
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    // Create the window
    mainWindowContext = glfwCreateWindow(width, height, "Regoc : Test OpenGL ", NULL, NULL);
    if (!mainWindowContext)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }
    
    // Get Buffer Size information
    glfwGetFramebufferSize(mainWindowContext, &bufferWidth, &bufferHeight);
    
    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindowContext);
    
    // Handle key and mouse input
    createInputCallbacks();
    glfwSetInputMode(mainWindowContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Allow modern extension features
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK)
    {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindowContext);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    glfwSetWindowUserPointer(mainWindowContext, this);
    
    // Setup Viewport size
    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    return 1;
}

Window::~Window() { 
    glfwDestroyWindow(mainWindowContext);
    glfwTerminate();
}

void Window::handleKeys(GLFWwindow *window, int key, int keycode, int action, int mode) { 
    Window* castWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            castWindow->keys[key] = true;
            //printf("Pressed: %d\n", key);
        }else if (action == GLFW_RELEASE){
            castWindow->keys[key] = false;
            //printf("Released: %d\n", key);
        }
    }
}

void Window::createInputCallbacks() { 
    glfwSetKeyCallback(mainWindowContext, handleKeys);
    glfwSetCursorPosCallback(mainWindowContext, handleMouse);
}

void Window::handleMouse(GLFWwindow *window, double xPos, double yPos) { 
    Window* castWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(castWindow->mouseFirstMoved){
        castWindow->lastX = xPos;
        castWindow->lastY = yPos;
        castWindow->mouseFirstMoved = false;
    }
    
    castWindow->xChange = xPos - castWindow->lastX;
    // For invert y cordinates
    //castWindow->yChange = yPos - castWindow->lastY;
    castWindow->yChange = castWindow->lastY - yPos;
    
    castWindow->lastX = xPos;
    castWindow->lastY = yPos;
    
    //printf("X:%.6f, Y:%.6f\n", castWindow->xChange, castWindow->yChange);
}

GLfloat Window::getYChanged() { 
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

GLfloat Window::getXChanged() { 
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}















