#include "Vertex.h"

// generate list of vertices
std::vector<Vertex> Vertex::genList(float *vertices, int noVertices)
{
    std::vector<Vertex> ret(noVertices);

    int stride = 8;

    for (int i = 0; i < noVertices; i++)
    {
        ret[i].pos = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]);

        ret[i].normal = glm::vec3(
            vertices[i * stride + 3],
            vertices[i * stride + 4],
            vertices[i * stride + 5]);

        ret[i].texCoord = glm::vec2(
            vertices[i * stride + 6],
            vertices[i * stride + 7]);
    }

    return ret;
}

void Vertex::averageVectors(glm::vec3 &baseVec, glm::vec3 addition, unsigned char existingContributions)
{
    if (!existingContributions)
    {
        baseVec = addition;
    }
    else
    {
        float f = 1 / ((float)existingContributions + 1);

        baseVec *= (float)(existingContributions)*f;

        baseVec += addition * f;
    }
}

// calculate tangent vectors for each face
void Vertex::calcTanVectors(std::vector<Vertex> &list, std::vector<unsigned int> &indices)
{
    unsigned char *counts = (unsigned char *)malloc(list.size() * sizeof(unsigned char));
    for (unsigned int i = 0, len = list.size(); i < len; i++)
    {
        counts[i] = 0;
    }

    // iterate through indices and calculate vectors for each face
    for (unsigned int i = 0, len = indices.size(); i < len; i += 3)
    {
        // 3 vertices corresponding to the face
        Vertex v1 = list[indices[i + 0]];
        Vertex v2 = list[indices[i + 1]];
        Vertex v3 = list[indices[i + 2]];

        // calculate edges
        glm::vec3 edge1 = v2.pos - v1.pos;
        glm::vec3 edge2 = v3.pos - v1.pos;

        // calculate dUVs
        glm::vec2 deltaUV1 = v2.texCoord - v1.texCoord;
        glm::vec2 deltaUV2 = v3.texCoord - v1.texCoord;

        // use inverse of the UV matrix to determine tangent
        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

        glm::vec3 tangent = {
            f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
            f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
            f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)};

        // average in the new tangent vector
        averageVectors(list[indices[i + 0]].tangent, tangent, counts[indices[i + 0]]++);
        averageVectors(list[indices[i + 1]].tangent, tangent, counts[indices[i + 1]]++);
        averageVectors(list[indices[i + 2]].tangent, tangent, counts[indices[i + 2]]++);
    }
}