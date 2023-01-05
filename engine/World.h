#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <map>
#include <string>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "WorldEntity.h"

class World
{
public:
	World();
	~World();
	void draw(Shader shader);
	void addModel(std::string name, Model *model);
	void addEntity(std::string name, WorldEntity *entity);
	std::map<std::string, Model *> _items;
	std::map<std::string,WorldEntity *> _entities;
private:
};

#endif