#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static std::vector<Vertex> GenerateList(float* vertices, int nVertices);
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t VAO;

    std::vector<Texture> textures;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures = {});

    void Render(Shader shader);
    void Cleanup();

private:
    uint32_t VBO, EBO;

    void Setup();
};

class Model
{
public:
    glm::vec3 pos;
    glm::vec3 size;
    
    Model(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f));

    void LoadModel(std::string path);

    virtual void Init();
    virtual void Render(Shader shader);

    void Cleanup();

protected:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> texturesLoaded;

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type);
};
