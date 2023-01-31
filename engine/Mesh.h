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
   Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

   GLuint VAO;
private:
   void setupMesh();
  
   GLuint VBO;
   GLuint EBO;
};


#endif