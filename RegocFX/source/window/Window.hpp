//
//  Window.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 04/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WND_CONST_WIDTH = 800;
const GLint WND_CONST_HEIGHT = 600;

class Window{
private:
    GLFWwindow *mainWindowContext;
    GLint width, height;
    GLint bufferWidth, bufferHeight;
    
    void createInputCallbacks();
    bool keys[1024];
    
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;
    
public:
    Window();
    Window(const GLint &windowWidth, const GLint &windowHeight);
    int windowInitialise();
    
    inline GLfloat getBufferWidth() { return bufferWidth; }
    inline GLfloat getBufferHeight() { return bufferHeight; }
    inline bool getShouldClose() { return glfwWindowShouldClose(mainWindowContext); }
    
    inline void swapBuffers(){ glfwSwapBuffers(mainWindowContext); }
    
    static void handleKeys(GLFWwindow* window, int key, int keycode, int action, int mode);
    static void handleMouse(GLFWwindow *window, double xPos, double yPos);
    
    inline bool* getKeys() { return keys; }
    GLfloat getXChanged();
    GLfloat getYChanged();
    
    ~Window();
};

#endif /* Window_hpp */
