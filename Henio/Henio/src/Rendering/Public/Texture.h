#pragma once
#include <cstdint>
#include <assimp/material.h>
#include <glad/glad.h>

class Texture
{
public:
    Texture();
    Texture(std::string dir, std::string path, aiTextureType type);

    void Generate();
    void Load(bool flip = true);
    
    void Bind();

    uint32_t id;
    std::string dir;
    std::string path;
    aiTextureType type;
};
