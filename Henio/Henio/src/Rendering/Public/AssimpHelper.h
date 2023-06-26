#pragma once
#include <cstdint>

struct aiScene;
struct aiMesh;
struct aiBone;

class AssimpHelper
{
public:
    static void ParseSingleBone(uint32_t boneIdx, const aiBone* bone);
    static void ParseMeshBones(const aiMesh* mesh);
    static void ParseMeshes(const aiScene* scene);
    static void ParseScene(const aiScene* scene);
};