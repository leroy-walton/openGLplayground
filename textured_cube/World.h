#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include<map>
#include<string>
#include"Shader.h"
#include"Camera.h"
#include"Model.h"
#include"WorldItem.h"

class World
{
	public:
		World();
		~World();
		void draw(Shader shader);
		void addModel(std::string name, Model* model);		
		std::map<std::string, Model*> _items;
	private:
		
};

#endif
