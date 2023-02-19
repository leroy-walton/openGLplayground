#ifndef FACTORY_H
#define FACTORY_H

#include <entt/entt.hpp>

class Factory
{
public:
    // planets
    static void makePlanets(entt::registry &registry)
    {
        const int numEntities = 20;
        for (int i = 0; i < numEntities; i++)
        {
            auto e = registry.create();
            registry.emplace<DynamicCube>(e);
            Transform &transform = registry.emplace<Transform>(e);
            transform.position.x = glm::linearRand(1, 100);
            transform.position.y = glm::linearRand(1, 100);
            transform.position.z = glm::linearRand(1, 100);
            transform.scale = glm::vec3(0.1f, 0.1f, 0.1f);
            auto &vel = registry.emplace<Velocity>(e);
            vel.velocity.x = 0;
            vel.velocity.y = 0;
            vel.velocity.z = 0;
            VisualShape &visuals = registry.emplace<VisualShape>(e);
            visuals.model = ResourceManager::getJupiterModel();
            visuals.shader = ResourceManager::getBasicShader();
        }
    }

    // static objects
    static void makeStaticObjects(entt::registry &registry)
    {
        // terrain
        {
            auto e = registry.create();
            Transform &tr = registry.emplace<Transform>(e);
            VisualShape &vs = registry.emplace<VisualShape>(e);
            vs.model = ResourceManager::getTerrainModel();
            vs.shader = ResourceManager::getBasicShader();
            tr.scale = glm::vec3(10000.f);
        }
        // barrell
        {
            auto e = registry.create();
            Transform &tr = registry.emplace<Transform>(e);
            VisualShape &vs = registry.emplace<VisualShape>(e);
            vs.model = ResourceManager::getBarrelModel();
            vs.shader = ResourceManager::getBasicShader();
            tr.position = glm::vec3(50.0, -1.0f, 0.0f);
            tr.scale = glm::vec3(20.f);
        }
        // suzanne
        {
            auto e = registry.create();
            Transform &tr = registry.emplace<Transform>(e);
            VisualShape &vs = registry.emplace<VisualShape>(e);
            vs.model = ResourceManager::getSuzanneModel();
            vs.shader = ResourceManager::getNormalColorShader();
            tr.position = glm::vec3(20.0, 35.0f, -100.0f);
            tr.scale = glm::vec3(10.f);
        }
    }

	// rotating cube
    static void makeRotatingCube(entt::registry &registry)
	{
		auto e = registry.create();
		registry.emplace<Rotating>(e);
		Transform &tr = registry.emplace<Transform>(e);
		VisualShape &vs = registry.emplace<VisualShape>(e);
		vs.model = ResourceManager::getSkullRatCubeModel();
		vs.shader = ResourceManager::getBasicShader();
		tr.position = glm::vec3(200.0, 35.0f, -100.0f);
		tr.scale = glm::vec3(10.f);
	}

    static entt::entity makeLight(entt::registry &registry)
    {
        auto lampEntity = registry.create();
        Transform &lampTransform = registry.emplace<Transform>(lampEntity);
        VisualShape &lampVs = registry.emplace<VisualShape>(lampEntity);
        lampVs.model = ResourceManager::getSphereModel();
        lampVs.shader = ResourceManager::getUniColorShader();
        lampTransform.scale = glm::vec3(30.f);
        return lampEntity;
    }
};

#endif