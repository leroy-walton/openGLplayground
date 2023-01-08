#include "Axes.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Axes::Axes()
{
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, // x-axis
        0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, // y-axis
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f  // z-axis
    };

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
}

Axes::~Axes()
{
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}

void Axes::draw()
{
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // red for x-axis
    glDrawArrays(GL_LINES, 0, 2);

    glColor3f(0.0f, 1.0f, 0.0f); // green for y-axis
    glDrawArrays(GL_LINES, 2, 2);

    glColor3f(0.0f, 0.0f, 1.0f); // blue for z-axis
    glDrawArrays(GL_LINES, 4, 2);
}
