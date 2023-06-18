#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection
{
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    // TODO: this should be in a transform component
    glm::vec3 cameraPos;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::vec3 worldUp;

    float yaw;
    float pitch;
    
    float speed;
    float fov;

    Camera(glm::vec3 position);

    void UpdateCameraDirection(double dx, double dy);
    void UpdateCameraPosition(CameraDirection cameraDirection, double deltaTime);
    void UpdateCameraFov(double dy);

    glm::mat4 GetViewMatrix();

private:
    void UpdateCameraVectors();
};