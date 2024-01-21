#pragma once
#include <glm/glm.hpp>
#include <vector>

class Window;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;
};

struct Mesh
{
    std::vector<Vertex> vertices;
};

struct RenderData {
    Window* window = nullptr;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int triangleCount = 0;
};