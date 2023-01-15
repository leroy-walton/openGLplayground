#include "WorldFactory.h"

World WorldFactory::generate()
{
    World world;    
    Shader basicShader("basic.vert", "basic.frag"); // compile shader
	Shader normalColorShader("normalColor.vert", "normalColor.frag");
	Shader uniColorShader("uniColor.vert", "uniColor.frag");

    world.basicShader = &basicShader;
    world.uniColorShader = &uniColorShader;
    world.normalColorShader = &normalColorShader;

    // models
	Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
	//Model sponzaModel("resources/models/sponza/Sponza.gltf");
	Model suzanneModel("resources/models/suzanne/Suzanne2.gltf");
	Model sphereModel("resources/models/sphere.gltf");
	Model terrainModel("resources/models/terrain/ground_textured_100x100.gltf");

    // // WorldEntities
    WorldEntity lamp("lamp", &sphereModel, world.uniColorShader );
	world.addEntity("lamp", &lamp);
    world.lamp = &lamp;
	 //WorldEntity sponza("sponza", &sponzaModel, &normalColorShader);
	 //WorldEntity sponza("sponza", &sponzaModel, &basicShader);
	 //world.addEntity("sponza", &sponza);
   	WorldEntity suzanne("suzanne", &suzanneModel, world.normalColorShader);
	world.addEntity("suzanne", &suzanne);
	WorldEntity barrel("barrel", &barrelModel, world.basicShader);
	world.addEntity("barrel", &barrel);
	WorldEntity terrain("terrain", &terrainModel, world.basicShader);
	world.addEntity("terrain", &terrain);

    // // positionning / scaling
    barrel.position = glm::vec3(50.0, -1.0f, 0.0f);
	barrel.scaleUp(glm::vec3(20.0f));
    suzanne.scaleUp(glm::vec3(30.0f));
	suzanne.translate(glm::vec3(-440.0f, 140.0f, -250.0f));
    
    lamp.scaleUp(glm::vec3(30.0f));
	terrain.scaleUp(glm::vec3(10000.0f));


}