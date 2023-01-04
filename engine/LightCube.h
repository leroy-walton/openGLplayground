#ifndef LIGHTCUBE_CLASS_H
#define LIGHTCUBE_CLASS_H

#include "Shader.h"
#include "Camera.h"
#include <glm/ext.hpp>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>

class LightCube
{
public:
    LightCube();
    void draw(Shader &shader);
    VAO *cubeVAO;
    VBO *cubeVBO;
    EBO *cubeEBO;
    std::vector<GLfloat> m_light_cube_vertices;
    std::vector<GLuint> m_light_cube_elements;
};

#endif
