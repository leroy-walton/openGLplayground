#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include "World.h"

class WorldRenderer
{
public:
    void render(World* world)
    {
        for (std::map<std::string, WorldEntity *>::iterator itr = world->_entities.begin(); itr != world->_entities.end(); ++itr)
        {
            std::string name = itr->first;
            WorldEntity *entity = itr->second;
            if (entity->isEnabled)
            {
                renderEntity(entity);
            }
        }
    }

private:
    void renderEntity(WorldEntity* entity)
    {
        if (entity->isEnabled)
        {
            entity->shader->Activate();
            GLint modelLoc = glGetUniformLocation(entity->shader->ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(entity->getMatrix()));

            Model *model = entity->getModel();

            for (GLuint i = 0; i < model->meshes.size(); i++)
            {
                renderMesh(model->meshes[i], entity->shader);
            }
        }
    }

    void renderMesh(Mesh &mesh, Shader *shader)
    {
        // Bind appropriate textures
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;

        for (GLuint i = 0; i < mesh.textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
            // Retrieve texture number (the N in diffuse_textureN)
            std::stringstream ss;
            std::string number;
            std::string name = mesh.textures[i].typeName;
            // TODO: typeName is always empty ?
            if (name == "texture_diffuse")
            {
                ss << diffuseNr++; // Transfer GLuint to stream
            }
            else if (name == "texture_specular")
            {
                ss << specularNr++; // Transfer GLuint to stream
            }

            number = ss.str();
            // Now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
            // And finally bind the texture
            glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
        }

        // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
        glUniform1f(glGetUniformLocation(shader->ID, "material.shininess"), 16.0f);

        // Draw mesh
        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Always good practice to set everything back to defaults once configured.
        for (GLuint i = 0; i < mesh.textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
};

#endif