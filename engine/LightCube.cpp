#include "LightCube.h"

LightCube::LightCube()
{
    std::vector<GLfloat> light_cube_vertices = {
        -0.1f, -0.1f, 0.1f,
        -0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, 0.1f};

    m_light_cube_vertices = light_cube_vertices;

    std::vector<GLuint> light_cube_elements = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7};
    m_light_cube_elements = light_cube_elements;

    cubeVAO = new VAO();
    cubeVAO->Bind();
    cubeVBO = new VBO(m_light_cube_vertices);
    cubeEBO = new EBO(m_light_cube_elements);
	
    cubeVAO->LinkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind all to prevent accidentally modifying them
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeEBO->Unbind();
};

void LightCube::draw(Shader &shader)
{
    cubeVAO->Bind();
    glDrawElements(GL_TRIANGLES, m_light_cube_elements.size(), GL_UNSIGNED_INT, 0);
    cubeVAO->Unbind();
}
