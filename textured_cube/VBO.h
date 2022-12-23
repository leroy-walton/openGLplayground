#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

// Structure to standardize the vertices used in the meshes

struct VertexStruct
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<VertexStruct> &vertices);
	VBO(std::vector<glm::mat4> &mat4s);
	VBO(GLfloat *vertices, GLsizeiptr size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif