#ifndef TEXTUREDCUBE_CLASS_H
#define TEXTUREDCUBE_CLASS_H

#include "Shader.h"
#include "Camera.h"
#include <glm/ext.hpp>
#include "stb/stb_image.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include "Texture.h"

class TexturedCube
{
public: 
    TexturedCube();
    void draw(Shader &shader, Camera &camera);
    VAO* cubeVAO;
    VBO* cubeVBO;
    EBO* cubeEBO;
    GLuint texture;
    std::vector<GLfloat> textured_cube_vertices;
    std::vector<GLuint> textured_cube_elements;
    };

#endif
