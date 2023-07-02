#pragma once

#include <map>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

#define MAX_NUM_BONES_PER_VERTEX 4

struct VertexBoneData
{
    uint32_t boneIds[MAX_NUM_BONES_PER_VERTEX] = {0};
    float weights[MAX_NUM_BONES_PER_VERTEX] = {0.0f};

    VertexBoneData() = default;

    void AddBoneData(uint32_t boneId, float weight);
};

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
    std::vector<VertexBoneData> bones;
    
    uint32_t VAO;

    std::vector<Texture> textures;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<VertexBoneData> bones, std::vector<Texture> textures = {});

    void Render(Shader shader);
    void Cleanup();

private:
    uint32_t VBO, EBO;
    GLuint boneBuffer = 0;

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

    std::map<std::string,uint32_t> boneNameToIndexMap;
    
    void ProcessNode(aiNode* node, const aiScene* scene);
    int32_t GetBoneId(const aiBone* bone);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const uint32_t meshIndex);
    std::vector<Texture> LoadTextures(aiMaterial* mat, aiTextureType type);
};
