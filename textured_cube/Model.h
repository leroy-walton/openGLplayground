#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"

class Model
{
public:
    std::vector<Mesh *> meshes;
};

#endif