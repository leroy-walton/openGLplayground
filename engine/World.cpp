#include "World.h"

World::World() {}

World::~World() {}

void World::addModel(std::string name, Model* model)
{
	_items[name] = model;
}

void World::draw(Shader shader)
{
	std::cout << "World::draw start\n";
	for (std::map<std::string,Model*>::iterator itr = _items.begin(); itr != _items.end(); ++itr) {
	 	std::string name = itr->first;
		Model* model = itr->second;
	    std::cout << name << " " << model->isEnabled << "\n";
	 	if (model->isEnabled ) {
	 		model->draw(shader);
	 	}
	}
	std::cout << "World::draw end\n";

}
