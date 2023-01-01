#include "ModelLoader.h"

void ModelLoader::load(std::string path, Model *model)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path,
                                           aiProcess_JoinIdenticalVertices |
                                               aiProcess_Triangulate |
                                               aiProcess_FlipUVs |
                                               aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Could not load model at " << path << std::endl
                  << import.GetErrorString() << std::endl;
        // return nullptr;
    }

    // parse directory from path
    std::string directory = path.substr(0, path.find_last_of("/"));

    std::cout << "importing model : " << path << "\n";
    std::cout << "     mNumMeshes : " << scene->mNumMeshes << "\n";
    std::cout << "  mNumMaterials : " << scene->mNumMaterials << "\n";
    std::cout << "   mNumTextures : " << scene->mNumTextures << "\n";
    std::cout << "           name : " << scene->mName.C_Str() << "\n";

    // Model model;
    processNode(scene->mRootNode, scene, model);
    std::cout << "all mesh processed : " << model->meshes.size() << "\n";
    //    std::cout << " vertices.size : " << model.meshes[0]->vertices.size() << "\n";
    //    std::cout << "  indices.size : " << model.meshes[0]->indices.size() << "\n";
    //    std::cout << " textures.size : " << model.meshes[0]->textures.size() << "\n";

    // return model;
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene, Model *model)
{
    // process all meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        std::cout << "   processing mesh number : " << i << "\n";
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "     mNumVertices : " << mesh->mNumVertices << "\n";
        std::cout << "        mNumFaces : " << mesh->mNumFaces << "\n";
        std::cout << " mNumUVComponents : " << mesh->mNumUVComponents << "\n";
        std::cout << "       HasNormals : " << mesh->HasNormals() << "\n";

        Mesh newMesh = processMesh(mesh, scene);
        model->meshes.push_back(&newMesh);
    }
    // process all child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, model);
    }

    std::cout << "all meshes processed : " << model->meshes.size() << "\n";
}

Mesh ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    std::cout << "processing vertices : " << mesh->mNumVertices << "\n";
    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // position
        vertices[i].pos = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z);

        std::cout << "position      " << vertices[i].pos.x << "  " << vertices[i].pos.y << "  " << vertices[i].pos.z << "\n";

        // determine if outside of current min and max
        /*
        for (int j = 0; j < 3; j++)
        {
            // if smaller than min
            if (vertices[i].pos[j] < min[j])
                min[j] = vertices[i].pos[j];
            // if larger than max
            if (vertices[i].pos[j] > max[j])
                max[j] = vertices[i].pos[j];
        }
        */
        // normal vectors
        vertices[i].normal = glm::vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z);

        std::cout << "normal    " << vertices[i].normal.x << "  " << vertices[i].normal.y << "  " << vertices[i].normal.z << "\n";

        // textures
        if (mesh->mTextureCoords[0])
        {
            vertices[i].texCoord = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y);
        }
        else
        {
            vertices[i].texCoord = glm::vec2(0.0f);
        }

        // tangent vector

        // vertices[i].tangent = {
        //     mesh->mTangents[i].x,
        //     mesh->mTangents[i].y,
        //     mesh->mTangents[i].z};
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "indices.size() : " << indices.size() << "\n";
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        std::cout << indices[i] << "\n";
    }

    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        /*
                if (States::isActive<unsigned int>(&switches, NO_TEX)) {
                    // use materials

                    // 1. diffuse colors
                    aiColor4D diff(1.0f);
                    aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff);
                    // 2. specular colors
                    aiColor4D spec(1.0f);
                    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec);

                    ret = Mesh(br, diff, spec);
                }
                else {
                    // use textures
        */
        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        // .obj, use aiTextureType_HEIGHT
        std::vector<Texture> normalMaps = loadTextures(material, aiTextureType_NORMALS);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // ret = Mesh(br, textures);
    }
    Mesh res;
    res.indices = indices;
    res.vertices = vertices;
    res.textures = textures;
    res.initVAO();
    return res;
}

std::vector<Texture> ModelLoader::loadTextures(aiMaterial *mat, aiTextureType type)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        /*
                // prevent duplicate loading
                bool skip = false;
                for (unsigned int j = 0; j < textures_loaded.size(); j++) {
                    if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                        textures.push_back(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }

                if (!skip) {
                    // not loaded yet
                    Texture tex(directory, str.C_Str(), type);
                    tex.load(false);
                    textures.push_back(tex);
                    textures_loaded.push_back(tex);
                }

        */
    }
    return textures;
}