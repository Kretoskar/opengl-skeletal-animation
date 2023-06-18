#include "Rendering/Public/Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Model::Model()
{
}

void Model::Init()
{
}

void Model::Render(Shader shader)
{
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
