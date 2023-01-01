#ifndef WOLDSITEM_CLASS_H
#define WORLDITEM_CLASS_H

#include"Model.h"

class WorldItem
{
	public:
		WorldItem(std::string name, Model* model);
		std::string getName();
		Model* getModel();
		void draw(Shader& shader);

		bool isEnabled=true;
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec4 rotation = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		
	private:
		std::string _name;
		Model* _model;

};

#endif

