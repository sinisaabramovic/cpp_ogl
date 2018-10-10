//
//  Mesh.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 03/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "OpenGL_Error_Assert.hpp"

void calcAverageNormals(unsigned int * indicies,
                        unsigned int indiciesCount,
                        GLfloat * vertices,
                        unsigned int verticesCount,
                        unsigned int vLength,
                        unsigned int normalOffset);

class Mesh{
private:
    GLuint _vao, _vbo, _ibo;
    GLsizei _indexCount;
public:
    Mesh();
    ~Mesh();
    
    void CreateMesh(GLfloat *vertices, unsigned int *indicies, unsigned int numOfVertices, unsigned int numberOfIndicies);
    void RenderMesh();
    void ClearMesh();
};

#endif /* Mesh_hpp */
