#include "TexturedCube.h"

TexturedCube::TexturedCube()
{
    std::vector<GLfloat> textured_cube_vertices = {
        // pos , col, uv, normals
        // front face
        -0.5, -0.5, 0.5,    1.0, 0.0, 0.0,      1.0, 1.0,       0.0, 0.0, 1.0,
        0.5, -0.5, 0.5,     0.0, 1.0, 0.0,      1.0, 0.0,       0.0, 0.0, 1.0,
        0.5, 0.5, 0.5,      0.0, 0.0, 1.0,      0.0, 0.0,       0.0, 0.0, 1.0,
        -0.5, 0.5, 0.5,     1.0, 1.0, 1.0,      0.0, 1.0,       0.0, 0.0, 1.0,
        // back face
        0.5, 0.5, -0.5, 0.0, 0.0, 1.0, 1.0, 1.0,        0.0, 0.0, -1.0,
        0.5, -0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0,       0.0, 0.0, -1.0,
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0,      0.0, 0.0, -1.0,
        -0.5, 0.5, -0.5, 1.0, 1.0, 1.0, 0.0, 1.0,       0.0, 0.0, -1.0,

        // right face
        0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0,       1.0, 0.0, 0.0, 
        0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0,        1.0, 0.0, 0.0,
        0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,         1.0, 0.0, 0.0,
        0.5, -0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0,        1.0, 0.0, 0.0,

        // left face
        -0.5, 0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0,      -1.0, 0.0, 0.0,
        -0.5, -0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0,      -1.0, 0.0, 0.0,
        -0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,       -1.0, 0.0, 0.0,
        -0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0,        -1.0, 0.0, 0.0,

        // bottom face 
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0,     0.0, -1.0, 0.0,
        0.5, -0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0,       0.0, -1.0, 0.0,
        0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,        0.0, -1.0, 0.0,
        -0.5, -0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0,       0.0, -1.0, 0.0,

        //top face
        0.5, 0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0,        0.0, 1.0, 0.0,
        -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0,       0.0, 1.0, 0.0,
        -0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,        0.0, 1.0, 0.0,
        0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0,          0.0, 1.0, 0.0
    };    

    m_textured_cube_vertices = textured_cube_vertices;

    std::vector<GLuint> textured_cube_elements = {
        0, 1, 2,
        2, 3, 0,
        // Left face
        4, 5, 6,
        6, 7, 4,
        // Right Face
        8, 9, 10,
        10, 11, 8,
        // Back face
        12, 13, 14,
        14, 15, 12,
        // Top face
        16, 17, 18,
        18, 19, 16,
        // Bottom face
        20, 21, 22,
        22, 23, 20};
    m_textured_cube_elements = textured_cube_elements;

    cubeVAO = new VAO();
    cubeVAO->Bind();
    cubeVBO = new VBO(m_textured_cube_vertices);
    cubeEBO = new EBO(m_textured_cube_elements);

    cubeVAO->LinkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);                   // position
    cubeVAO->LinkAttrib(*cubeVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float))); // colors
    cubeVAO->LinkAttrib(*cubeVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float))); // texCoord
    cubeVAO->LinkAttrib(*cubeVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float))); // texCoord
    // Unbind all to prevent accidentally modifying them
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeEBO->Unbind();

    Texture tex(".", "resources/textures/3dfx-chip.png", aiTextureType_NONE);
    tex.load(1);
    texture = tex.id;
};

void TexturedCube::draw(Shader &shader, Camera &camera)
{
    GLint textureUniformLocation = glGetUniformLocation(shader.ID, "tex0");
    glUniform1i(textureUniformLocation, 0); // 0 corresponds to GL_TEXTURE0 ?
    glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture before drawing
    cubeVAO->Bind();
    glDrawElements(GL_TRIANGLES, m_textured_cube_elements.size(), GL_UNSIGNED_INT, 0);
    cubeVAO->Unbind();
}

