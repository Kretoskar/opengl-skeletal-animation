#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WorldUp glm::vec3(0.0f, 1.0f, 0.0f)

struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void SetPitch(float inPitch) { rotation.x = inPitch;  }
    void SetYaw(float inYaw) { rotation.y = inYaw;  }
    void SetRoll(float inRoll) { rotation.z = inRoll;  }

    //TODO: recalculate this stuff in a separate system
    glm::vec3 GetFrontVector()
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        direction.y = sin(glm::radians(rotation.x));
        direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.y));

        return glm::normalize(direction);
    }
    
    glm::vec3 GetRightVector()
    {
        return glm::normalize(glm::cross(GetFrontVector(), WorldUp));
    }
    
    glm::vec3 GetUpVector()
    {
        glm::normalize(glm::cross(GetRightVector(), GetFrontVector()));
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + GetFrontVector(), GetUpVector());
    }
};