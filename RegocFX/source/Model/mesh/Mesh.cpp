//
//  Mesh.cpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 03/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#include "Mesh.hpp"


void calcAverageNormals(unsigned int * indicies,
                        unsigned int indiciesCount,
                        GLfloat * vertices,
                        unsigned int verticesCount,
                        unsigned int vLength,
                        unsigned int normalOffset)
{

    for (size_t i = 0; i < indiciesCount; i += 3)
    {
        unsigned int in0 = indicies[i] * vLength;
        unsigned int in1 = indicies[i + 1] * vLength;
        unsigned int in2 = indicies[i + 2] * vLength;
        
        glm::vec3 v1(vertices[in1] - vertices[in0],
                     vertices[in1 + 1] - vertices[in0 + 1],
                     vertices[in1 + 2] - vertices[in0 + 2]);
        
        glm::vec3 v2(vertices[in2] - vertices[in0],
                     vertices[in2 + 1] - vertices[in0 + 1],
                     vertices[in2 + 2] - vertices[in0 + 2]);
        
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);
        
        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        
        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;
        
        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;
        
        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
        
    }
    
    for (size_t i = 0; i < verticesCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }
}

void Mesh::ClearMesh()
{
    if(_ibo != 0){
        GLCall(glDeleteBuffers(1, &_ibo));
        _ibo = 0;
    }
    if(_vbo != 0){
        GLCall(glDeleteBuffers(1, &_vbo));
        _vbo = 0;
    }
    if(_vao != 0){
        GLCall(glDeleteVertexArrays(1, &_vao));
        _vao = 0;
    }
    
    _indexCount = 0;
}


void Mesh::RenderMesh()
{
    if(_vao != 0 && _ibo != 0){
        GLCall(glBindVertexArray(_vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
        GLCall(glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}


void Mesh::CreateMesh(GLfloat *vertices,
                      unsigned int *indicies,
                      unsigned int numOfVertices,
                      unsigned int numberOfIndicies)
{
    _indexCount = numberOfIndicies;
    
   
    GLCall(glGenVertexArrays(1, &_vao));
    GLCall(glBindVertexArray(_vao));
    
    GLCall(glGenBuffers(1, &_ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * numberOfIndicies, indicies, GL_STATIC_DRAW));
    
    GLCall(glGenBuffers(1, &_vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW));
    
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));
    
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3)));
    GLCall(glEnableVertexAttribArray(1));
    
    GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 5)));
    GLCall(glEnableVertexAttribArray(2));
    
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}


Mesh::~Mesh()
{
    ClearMesh();
}


Mesh::Mesh() :
_vao(0), _vbo(0), _ibo(0), _indexCount(0)
{
    
}
