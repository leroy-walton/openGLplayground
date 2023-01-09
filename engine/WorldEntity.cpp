#include "WorldEntity.h"
#
WorldEntity::WorldEntity(std::string name, Model *model, Shader *s)
{
	_name = name;
	_model = model;
	isEnabled = true;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	shader = s;
}

Model *WorldEntity::getModel()
{
	return _model;
}

std::string WorldEntity::getName()
{
	return _name;
}

void WorldEntity::draw()
{
	if (isEnabled)
	{
		shader->Activate();
		GLint modelLoc = glGetUniformLocation(shader->ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(getMatrix()));
		_model->draw(*shader);
	}
}

void WorldEntity::translate(glm::vec3 t) { position += t; }
void WorldEntity::setPosition(glm::vec3 p) { position = p; }
glm::vec3 WorldEntity::getPosition() { return position; }

// Orientation
void WorldEntity::rotate(float angle, glm::vec3 axis)
{
	orientation = glm::rotate(orientation, angle, axis);
}

void WorldEntity::setOrientation(glm::mat4 o) { orientation = o; }
glm::mat4 WorldEntity::getOrientation() { return orientation; }

// Scaling
void WorldEntity::scaleUp(glm::vec3 s) { scale *= s; }
void WorldEntity::setScale(glm::vec3 s) { scale = s; }
glm::vec3 WorldEntity::getScale() { return scale; }

glm::mat4 WorldEntity::getMatrix()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotate = orientation;
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), this->scale);
	return translate * rotate * scale;
}