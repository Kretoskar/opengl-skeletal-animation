#include "Components/Public/Camera.h"

Camera::Camera(glm::vec3 position)
    : cameraPos(position),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f),
    pitch(0.0f),
    speed(2.5f),
    fov(45.0f)
{
    UpdateCameraVectors();
}

void Camera::UpdateCameraDirection(double dx, double dy)
{
    yaw += dx;
    pitch += dy;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    UpdateCameraVectors();
}

void Camera::UpdateCameraPosition(CameraDirection cameraDirection, double deltaTime)
{
    float velocity = static_cast<float>(deltaTime) * speed;
    
    //TODO: rewrite this piece of shit
    switch (cameraDirection)
    {
        case CameraDirection::FORWARD:
            cameraPos += cameraFront * velocity;
            break;
         case CameraDirection::BACKWARD:
             cameraPos -= cameraFront * velocity;
            break;
        case CameraDirection::RIGHT:
            cameraPos += cameraRight * velocity;
            break;
        case CameraDirection::LEFT:
            cameraPos -= cameraRight * velocity;
            break;
        case CameraDirection::UP:
            cameraPos += cameraUp * velocity;
            break;
        case CameraDirection::DOWN:
            cameraPos -= cameraUp * velocity;
            break;
        case CameraDirection::NONE:
            break;
        default:
            break;
    }
}

void Camera::UpdateCameraFov(double dy)
{
    fov -= dy;
    fov = glm::clamp(fov, 1.0f, 45.0f);
}

float Camera::GetFov()
{
    return fov;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
   // cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}
