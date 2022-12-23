#ifndef CUBEMAP_CLASS_H
#define CUBEMAP_CLASS_H

#include"Shader.h"
#include"Camera.h"
#include<glm/ext.hpp>
#include"stb/stb_image.h"
class CubeMap
{
	public:
		CubeMap();
		void draw(Shader& skyboxShader,Camera& camera);
        unsigned int getSkyBoxVAO();
		unsigned int getTexture();
    private:
		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;

};

#endif