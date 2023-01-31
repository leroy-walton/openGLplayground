#ifndef WORLDENTITY_CLASS_H
#define WORLDENTITY_CLASS_H

#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class WorldEntity
{
public:
	WorldEntity(std::string name, Model *model, Shader *s);
	std::string getName();
	Model *getModel();

	void translate(glm::vec3 t);
	void setPosition(glm::vec3 p);
	glm::vec3 getPosition();

	void rotate(float angle, glm::vec3 axis);
	void setOrientation(glm::mat4 o);
	glm::mat4 getOrientation();

	void scaleUp(glm::vec3 s);
	void setScale(glm::vec3 s);
	glm::vec3 getScale();

	glm::mat4 getMatrix();

	bool isEnabled = true;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 orientation = glm::mat4(1.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Shader *shader;

private:
	std::string _name;
	Model *_model;
};

#endif
