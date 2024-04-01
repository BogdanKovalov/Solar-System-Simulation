#include "Camera.h"
#include "Aplication.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 Location, glm::vec3 TargetView) : Velocity(0.0f)
{
    this->Location = Location;
    auto API = Aplication::GetAPI();
    if (API)
    {
        glm::vec3 WorldUp = Aplication::GetAPI()->GetWorldUp();
        ForwardVector = glm::normalize(Location - TargetView);
        RightVector = glm::normalize(glm::cross(ForwardVector, WorldUp));
        UpVector = glm::cross(RightVector, ForwardVector);
    }
}

void Camera::Rotate(glm::vec2 YawAndPitch)
{
    YawAndPitch = YawAndPitch * 0.01f;

    glm::mat4 RotationMatrix(1.0f);

    RotationMatrix = glm::mat4(1.0f);
    RotationMatrix = glm::rotate(RotationMatrix, glm::radians(YawAndPitch.y), -RightVector);

    ForwardVector = RotationMatrix * glm::vec4(ForwardVector, 1.0f);
    RightVector = RotationMatrix * glm::vec4(RightVector, 1.0f);
    UpVector = RotationMatrix * glm::vec4(UpVector, 1.0f);

    RotationMatrix = glm::mat4(1.0f);
    RotationMatrix = glm::rotate(RotationMatrix, glm::radians(YawAndPitch.x), UpVector);

    ForwardVector = RotationMatrix * glm::vec4(ForwardVector, 1.0f);
    RightVector = RotationMatrix * glm::vec4(RightVector, 1.0f);
    UpVector = RotationMatrix * glm::vec4(UpVector, 1.0f);

    ForwardVector = glm::normalize(ForwardVector);
    RightVector = glm::normalize(RightVector);
    UpVector = glm::normalize(UpVector);
}

void Camera::Tick(float DeltaTime)
{
    // AddOffset(Velocity * DeltaTime);
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