#include <GL/glew.h>
#include <stb_image.h>

int main()
{

    // Load the texture image file into memory
    int width, height, channels;
    unsigned char *image = stbi_load("texture.jpg", &width, &height, &channels, STBI_rgb_alpha);

    // Generate a texture object and bind it
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data to the graphics card
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the image data, as it is now stored on the graphics card
    stbi_image_free(image);

    // Enable texturing in the shader
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "   TexCoord = aTexCoord;\n"
                                     "}\n";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "in vec2 TexCoord;\n"
                                       "out vec4 FragColor;\n"
                                       "uniform sampler2D ourTexture;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = texture(ourTexture, TexCoord);\n"
                                       "}\n";

    // Compile and link the shaders into a program
    GLuint shaderProgram = compileAndLinkShaders(vertexShaderSource, fragmentShaderSource);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set the texture unit for the sampler2D uniform in the fragment shader
    GLint textureUniformLocation = glGetUniformLocation(shaderProgram, "ourTexture");
    glUniform1i(textureUniformLocation, 0); // 0 corresponds to GL_TEXTURE0

    // Bind the texture before drawing
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the vertex data and indices
    float vertices[] = {...};       // vertex positions and texture coordinates
    unsigned int indices[] = {...}; // indices of the vertices

    // Generate a vertex buffer object and bind it
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set the vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Generate an index buffer object and bind it
    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Set the indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Draw the cube
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteBuffers(1, &IBO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
}