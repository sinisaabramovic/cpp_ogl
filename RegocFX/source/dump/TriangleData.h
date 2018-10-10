//
//  TriangleData.h
//  RegocFX
//
//  Created by Sinisa Abramovic on 05/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef TriangleData_h
#define TriangleData_h
#include <GLFW/glfw3.h>

unsigned int triangle_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

GLfloat triangle_vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};

#endif /* TriangleData_h */
