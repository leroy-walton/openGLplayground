#ifndef JAM_ENTITY_H
#define JAM_ENTITY_H

#include <memory>

#include "Model.h"

namespace jam
{
    class Entity
    {
    public:
        using id_t = unsigned int;

        static Entity createEntity()
        {
            static id_t currentId = 0;
            return Entity{currentId++};
        }

        Entity(const Entity &) = delete;
        Entity &operator=(const Entity &) = delete;
        Entity(Entity &&) = default;
        Entity &operator=(Entity &&) = default;

        id_t getId() { return id; }

        Model *model;
        Shader *shader;

    private:
        Entity(id_t _id) : id{_id} {};

        id_t id;
    };

} // namespace jam

#endif