#pragma once

#include <vector>

#include "Mesh.h"

class Model
{
public:
    std::vector<Mesh> meshes;

    Model();
    
    virtual void Init();
    virtual void Render(Shader shader);
    void Cleanup();
};
