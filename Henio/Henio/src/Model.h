#pragma once
#include "RenderData.h"

class Model
{
public:
    void Init();
    Mesh GetVertexData();

private:
    Mesh vertexData;
};
