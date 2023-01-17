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
	void draw();
	void addEntity(std::string name, WorldEntity *entity);
	std::map<std::string, Model *> _items;
	std::map<std::string,WorldEntity *> _entities;

    Shader* basicShader;
    Shader* uniColorShader;
    Shader* normalColorShader;
	WorldEntity* lamp;

private:
};

#endif
