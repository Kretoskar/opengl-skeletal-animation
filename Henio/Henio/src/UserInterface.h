#pragma once
#include "RenderData.h"

class UserInterface
{
public:
    void Init(RenderData& renderData);
    void CreateFrame(RenderData& renderData);
    void Render();
    void Cleanup();
};
