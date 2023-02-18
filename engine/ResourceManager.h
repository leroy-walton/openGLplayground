#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Shader.h"
#include "Model.h"

class ResourceManager
{
public:
    // shaders
    static ResourceManager getInstance() {
        static ResourceManager shaderManager;
        return shaderManager;
    }

    static Shader* getBasicShader() {
        static Shader m_basicShader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
        return &m_basicShader;
    }

    static Shader* getNormalColorShader() {
        static Shader m_normalColorShader("resources/shaders/normalColor.vert", "resources/shaders/normalColor.frag");
        return &m_normalColorShader;
    }

    static Shader* getUniColorShader() {
        static Shader m_uniColorShader("resources/shaders/uniColor.vert", "resources/shaders/uniColor.frag");
        return &m_uniColorShader;
    }

    // models
    static Model* getBarrelModel() {
        static Model barrelModel("resources/models/wine_barrel/wine_barrel_01_4k.gltf");
        return &barrelModel;
    }

    static Model* getSphereModel() {
        static Model sphereModel("resources/models/sphere.gltf");
        return &sphereModel;
    }

    static Model* getTerrainModel() {
	    static Model terrainModel("resources/models/terrain/ground_textured_100x100.gltf");
        return &terrainModel;
    }

    static Model* getSkullRatCubeModel() {
	    static Model skullRatCubeModel("resources/models/cubeskullrat/cube_skull_rat.gltf");
        return &skullRatCubeModel;
    }

    static Model* getSuzanneModel() {
	    static Model suzanneModel("resources/models/suzanne/Suzanne2.gltf");
        return &suzanneModel;
    }

    static Model* getJupiterModel() {
	    static Model jupiterModel("resources/models/jupiter/scene.gltf");
        return &jupiterModel;
    }

private:
    ResourceManager(){};
};

#endif