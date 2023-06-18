#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 pos;
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
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);

    void Render(Shader shader);
    void Cleanup();

private:
    uint32_t VBO, EBO;

    void Setup();
};
