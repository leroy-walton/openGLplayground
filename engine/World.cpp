#include "World.h"

World::World() 
{
	Shader basicShader("basic.vert", "basic.frag"); // compile shader
	Shader normalColorShader("normalColor.vert", "normalColor.frag");
	Shader uniColorShader("uniColor.vert", "uniColor.frag");
	this->basicShader = &basicShader;
	this->normalColorShader = &normalColorShader;
	this->uniColorShader = &uniColorShader;

	std::cout << "basicShader.ID = " << basicShader.ID << "\n";
	std::cout << "normalColorShader.ID = " << normalColorShader.ID << "\n";
	std::cout << "uniColorShader.ID = " << uniColorShader.ID << "\n";

	std::cout << "this->basicShader.ID = " << this->basicShader->ID << "\n";
	std::cout << "this->normalColorShader.ID = " << this->normalColorShader->ID << "\n";
	std::cout << "this->uniColorShader.ID = " << this->uniColorShader->ID << "\n";

	std::cout << "this->basic address = " << this->basicShader <<  "\n";
	std::cout << "basic address       = " << &basicShader << "\n";

	//Model yModel("resources/models/axes/y.gltf");
	//WorldEntity axis_y("axis_y", &yModel, &basicShader);
	//addEntity("axis_y", &axis_y);

}

World::~World() {}

void World::addEntity(std::string name, WorldEntity *entity)
{
	_entities[name] = entity;
}

void World::draw()
{
	for (std::map<std::string, WorldEntity *>::iterator itr = _entities.begin(); itr != _entities.end(); ++itr)
	{
		std::string name = itr->first;
		WorldEntity *entity = itr->second;
		if (entity->isEnabled)
		{
			entity->draw();
		}
	}
}