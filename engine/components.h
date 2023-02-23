#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

struct DynamicCube {};
struct Rotating {};
struct Robot {};

struct Transform {
    glm::vec3 position{0.f};
    glm::vec3 scale{1.0f};
    glm::mat4 orientation{1.0f};
};

struct Velocity {
    glm::vec3 velocity{};
};

struct VisualShape {
    Model* model;
    Shader* shader;
};

#endif