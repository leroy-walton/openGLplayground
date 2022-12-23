#ifndef MODELLOADER_CLASS_H
#define MODELLOADER_CLASS_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include<iostream>
#include<vector>

class ModelLoader
{
 public:
    void load(std::string file, Model* model);
 private:
    void processNode(aiNode* node, const aiScene* scene, Model* model);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type);
};

#endif