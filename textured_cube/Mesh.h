#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include"Texture.h"
#include"Vertex.h"
#include<vector>

class Mesh
{
 public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    void initVAO();
    void Draw();
 private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

#endif