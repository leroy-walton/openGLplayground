#include "WorldEntity.h"

WorldEntity::WorldEntity(std::string name, Model *model)
{
	_name = name;
	_model = model;
	isEnabled = true;
}

Model *WorldEntity::getModel()
{
	return _model;
}

std::string WorldEntity::getName()
{
	return _name;
}

void WorldEntity::draw(Shader &shader)
{
	_model->draw(shader);
}