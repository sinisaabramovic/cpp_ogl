//
//  Model.hpp
//  RegocFX
//
//  Created by Sinisa Abramovic on 16/09/2018.
//  Copyright © 2018 Sinisa Abramovic. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"

class Model{
private:
    
    std::vector<Mesh*> meshList;
    std::vector<Texture*> textureList;
    std::vector<unsigned int> meshToTexture;
    
    
    void LoadNode(aiNode *node, const aiScene *scene);
    void LoadMesh(aiMesh *mesh, const aiScene *scene);
    void LoadMaterials(const aiScene *scene);
    
public:
    Model();
    
    void LoadModel(const std::string& fileName);
    void RenderModel();
    void ClearModel();
    
    ~Model();
};

#endif /* Model_hpp */
