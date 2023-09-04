#pragma once
#include <glm/vec3.hpp>

struct CameraComponent
{
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    
    float speed = 0;
    float fov = 0;
};
