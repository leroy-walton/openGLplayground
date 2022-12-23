#ifndef VERTEX_CLASS_H
#define VERTEX_CLASS_H

#include<glm/glm.hpp>
#include<vector>

struct Vertex {
 public:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;

    // generate list of vertices
    static std::vector<Vertex> genList(float* vertices, int noVertices);

    // calculate tangent vectors for each face
 private:
    static void averageVectors(glm::vec3& baseVec, glm::vec3 addition, unsigned char existingContributions);
    static void calcTanVectors(std::vector<Vertex>& list, std::vector<unsigned int>& indices);
};

#endif