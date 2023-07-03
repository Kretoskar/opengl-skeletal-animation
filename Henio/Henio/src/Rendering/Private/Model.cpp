#include "Rendering/Public/Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/postprocess.h>

#include "Rendering/Public/AssimpHelper.h"

static glm::mat4 mat4_cast(const aiMatrix4x4 &m) { return glm::transpose(glm::make_mat4(&m.a1)); }

std::vector<Vertex> Vertex::GenerateList(float* vertices, int nVertices)
{
    std::vector<Vertex> ret(nVertices);

    constexpr int stride = sizeof(Vertex) / sizeof(float);

    for(int i = 0; i < nVertices; i++)
    {
        ret[i].pos = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]
        );

        ret[i].normal = glm::vec3(
            vertices[i * stride + 3],
            vertices[i * stride + 4],
            vertices[i * stride + 5]
        );
        
        ret[i].texCoord = glm::vec2(
            vertices[i * stride + 6],
            vertices[i * stride + 7]
        );
    }

    return ret;
}

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<VertexBoneData> bones, std::vector<Texture> textures)
    : vertices(vertices), indices(indices), bones(bones), textures(textures)
{
    Setup();
}

void Mesh::Render(Shader shader)
{
    uint32_t diffuseIdx = 0;
    uint32_t specularIdx = 0;

    for (uint32_t i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        
        std::string name;
        switch (textures[i].type) {
            case aiTextureType_DIFFUSE:
                name = "diffuse" + std::to_string(diffuseIdx++);
                break;
            case aiTextureType_SPECULAR:
                name = "specular" + std::to_string(specularIdx++);
                break;
            default: ;
        }

        shader.SetInt(name, i);
        textures[i].Bind();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::Setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    //vertex.position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((offsetof(Vertex, pos))));

    //vertex.normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((offsetof(Vertex, normal))));
    
    //vertex.texcoord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((offsetof(Vertex, texCoord))));

    glGenBuffers(1, &boneBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, boneBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, MAX_NUM_BONES_PER_VERTEX, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, MAX_NUM_BONES_PER_VERTEX, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(MAX_NUM_BONES_PER_VERTEX * sizeof(int32_t)));

    glBindVertexArray(0);
}


void VertexBoneData::AddBoneData(uint32_t boneId, float weight)
{
    for (uint32_t i = 0; i < std::size(boneIds); i++)
    {
        if (weights[i] == 0.0f)
        {
            boneIds[i] = boneId;
            weights[i] = weight;
            return;
        }
    }
}

Model::Model(glm::vec3 pos, glm::vec3 size)
    : pos(pos), size(size) {}

void Model::LoadModel(std::string path)
{
    scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    AssimpHelper::ParseScene(scene);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Could not load model at " << path << std::endl << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of("/"));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all meshes
    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene, i));
    }

    // process children
    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

int32_t Model::GetBoneId(const aiBone* bone)
{
    int boneIndex = 0;
    std::string boneName(bone->mName.C_Str());

    if (boneNameToIndexMap.find(boneName) == boneNameToIndexMap.end()) {
        // Allocate an index for a new bone
        boneIndex = static_cast<int32_t>(boneNameToIndexMap.size());
        boneNameToIndexMap[boneName] = boneIndex;
    }
    else {
        boneIndex = boneNameToIndexMap[boneName];
    }

    return boneIndex;
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const uint32_t meshIndex)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;
    std::vector<VertexBoneData> bones;

    for (uint64_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        vertex.pos = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        vertex.normal = glm::vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );

        if (mesh->mTextureCoords[0])
        {
            vertex.texCoord = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else
        {
            vertex.texCoord = glm::vec2(0.0f);
        }

        vertices.push_back(vertex);
    }

    // fix it
    bones.reserve(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        bones.emplace_back();
    }

    for (uint64_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (uint64_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = LoadTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    for (uint32_t i = 0; i < mesh->mNumBones; i++)
    {
        const aiBone* bone = mesh->mBones[i];
        int32_t boneId = GetBoneId(bone);

        if (boneId == boneInfos.size())
        {
            BoneInfo bi(mat4_cast(bone->mOffsetMatrix));
            boneInfos.push_back(bi);
        }

        for (uint32_t i = 0; i < bone->mNumWeights; i++)
        {
            const aiVertexWeight& vw = bone->mWeights[i];
            uint32_t globalVertexId = bone->mWeights[i].mVertexId;
            bones[globalVertexId].AddBoneData(boneId, vw.mWeight);
        }
    }
    

    return Mesh(vertices, indices, bones, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<Texture> textures;

    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString path;
        mat->GetTexture(type, i, &path);
        std::cout << path.C_Str() << std::endl;

        // prevent duplicate loading
        bool skip = false;
        for (uint32_t j = 0; j < texturesLoaded.size(); j++)
        {
            if (std::strcmp(texturesLoaded[j].path.data(), path.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            Texture tex(directory, path.C_Str(), type);
            tex.Load(false);
            textures.push_back(tex);
            texturesLoaded.push_back(tex);
        }
    }
    
    return textures;
}

void Model::ReadNodeHierarchy(const aiNode* node, const glm::mat4& parentTransform)
{
    std::string nodeName = node->mName.data;
    glm::mat4 nodeTransform (mat4_cast(node->mTransformation));

 //   printf("%s - ", nodeName.c_str());

    glm::mat4 globalTransform = parentTransform * nodeTransform;
    if (boneNameToIndexMap.find(nodeName) != boneNameToIndexMap.end())
    {
        uint32_t boneIndex = boneNameToIndexMap[nodeName];
        boneInfos[boneIndex].finalTransform = globalTransform * boneInfos[boneIndex].offsetMatrix;
    }

    for (uint32_t i = 0 ; i < node->mNumChildren; i++)
    {
        ReadNodeHierarchy(node->mChildren[i], globalTransform);
    }
}


void Model::Init()
{
}

void Model::Render(Shader shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, size);
    shader.SetMat4("model", model);

    shader.SetFloat("material.shininess", 0.5f);
    
    for (Mesh mesh : meshes)
    {
        mesh.Render(shader);
    }
}

void Model::Cleanup()
{
    for (Mesh mesh : meshes)
    {
        mesh.Cleanup();
    }
}

void Model::GetBoneTransforms(std::vector<glm::mat4>& transforms)
{
    transforms.resize(boneInfos.size());
    glm::mat4 identity = glm::mat4(1.0f);

    ReadNodeHierarchy(scene->mRootNode, identity);

    for (uint32_t i = 0; i < boneInfos.size(); i++)
    {
        transforms[i] = boneInfos[i].finalTransform;
    }
}
