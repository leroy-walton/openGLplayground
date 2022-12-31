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

using namespace std;

class Model
{
public:
    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model( GLchar *path );
    // Draws the model, and thus all its meshes
    void draw(Shader shader);
    
private:
    /*  Model Data  */
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel( string path );
    void processNode( aiNode* node, const aiScene* scene );
    Mesh processMesh( aiMesh *mesh, const aiScene *scene );
};

#endif
