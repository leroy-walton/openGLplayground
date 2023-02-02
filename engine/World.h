#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <map>
#include <string>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "WorldEntity.h"
#include "entt/entt.hpp"

class World
{
public:
	World();
	~World();
	void addEntity(std::string name, WorldEntity *entity);
	std::map<std::string,WorldEntity *> _entities;

    entt::registry registry;

    Shader* basicShader;
    Shader* uniColorShader;
    Shader* normalColorShader;
	WorldEntity* lamp;

private:
};

#endif
