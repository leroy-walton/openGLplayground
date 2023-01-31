#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
public:
    Model(GLchar *path);

    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded; // Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
private:
    void loadModel(std::string path);     // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif
