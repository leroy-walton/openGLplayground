#include"WorldItem.h"

WorldItem::WorldItem(std::string name, Model* model) {
	_name = name;
	_model = model;
	isEnabled = true;
}

Model* WorldItem::getModel() {
	return _model;
}

std::string WorldItem::getName() {
	return _name;
}

void WorldItem::draw(Shader& shader)
{
	_model->draw(shader);
}