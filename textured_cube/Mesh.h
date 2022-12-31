#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "Texture.h"
#include "Vertex.h"
#include <vector>

#include "Shader.h"

class Mesh
{
public:
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;
   std::vector<Texture> textures;
   void initVAO();
   void Draw(Shader shader);
   Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

private:
   void setupMesh();
   GLuint VAO;
   GLuint VBO;
   GLuint EBO;
};


#endif