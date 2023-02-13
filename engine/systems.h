#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <entt/entt.hpp>

#include "components.h"

class RotationSystem
{
public:
    void update(entt::registry &registry)
    {
        auto view = registry.view<Rotating>();
        for(auto en : view) {
            Transform& tr = registry.get<Transform>(en);
            tr.orientation = glm::rotate(tr.orientation, 0.04f, glm::vec3(0.f, 1.f, 0.f ));
        }
    }
};


class RenderSystem
{
public:
    
    void render(entt::registry &registry)
    {
        auto view = registry.view<VisualShape>();
        for(auto entity: view) {
            Transform tr = registry.get<Transform>(entity);
            VisualShape vs = registry.get<VisualShape>(entity);

            vs.shader->Activate();

            // compute model matrix 
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), tr.position);
	        glm::mat4 rotate = tr.orientation;
	        glm::mat4 scale = glm::scale(glm::mat4(1.0f), tr.scale);
	        glm::mat4 res = translate * rotate * scale;

            GLint modelLoc = glGetUniformLocation(vs.shader->ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(res));

            Model *model = vs.model;
            for (GLuint i = 0; i < model->meshes.size(); i++)
            {
                renderMesh(model->meshes[i], vs.shader);
            }
        }
    }


private:
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
