#include "World.h"

World::World() {}

World::~World() {}

void World::addModel(std::string name, Model *model)
{
	_items[name] = model;
}

void World::addEntity(std::string name, WorldEntity *entity)
{
	_entities[name] = entity;
}

void World::draw(Shader shader)
{
	std::cout << "World::draw start\n";
	for (std::map<std::string, WorldEntity *>::iterator itr = _entities.begin(); itr != _entities.end(); ++itr)
	{
		std::string name = itr->first;
		WorldEntity *entity = itr->second;
		std::cout << name << " " << entity->isEnabled << "\n";
		if (entity->isEnabled)
		{
			entity->draw(shader);
		}
	}
	std::cout << "World::draw end\n";
}
