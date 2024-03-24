#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 Location, glm::vec3 TargetView, glm::vec3 WorldUp)
{
    this->Location = Location;
    ForwardVector = glm::normalize(Location - TargetView);
    RightVector = glm::normalize(glm::cross(ForwardVector, WorldUp));
    UpVector = glm::cross(ForwardVector, RightVector);
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::mat4 VectorMatrix = glm::mat4(
        glm::vec4(RightVector, 0.0f), glm::vec4(UpVector, 0.0f), glm::vec4(ForwardVector, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 PositionMatrix(1.0f);
    PositionMatrix = glm::translate(PositionMatrix, -Location);

    glm::mat4 ViewMatrix = VectorMatrix * PositionMatrix;
    return ViewMatrix;
}