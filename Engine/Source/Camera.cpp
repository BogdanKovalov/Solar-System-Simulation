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
    Rotation += glm::vec3(YawAndPitch, 0.0f);
    if (Rotation.y >= 90.0f)
    {
        Rotation.y = 89.9f;
    }
    if (Rotation.y <= -90.0f)
    {
        Rotation.y = -89.9f;
    }

    ForwardVector.z = cos(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));
    ForwardVector.y = sin(glm::radians(Rotation.y));
    ForwardVector.x = sin(glm::radians(Rotation.x)) * cos(glm::radians(Rotation.y));

    ForwardVector = glm::normalize(ForwardVector);
    RightVector = glm::normalize(glm::cross(ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
    UpVector = glm::cross(RightVector, ForwardVector);
}

//void Camera::Tick(float DeltaTime)
//{
//    // AddOffset(Velocity * DeltaTime);
//}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::mat4 VectorMatrix = glm::mat4(
        glm::vec4(RightVector, 0.0f), glm::vec4(UpVector, 0.0f), glm::vec4(ForwardVector, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 PositionMatrix(1.0f);
    PositionMatrix = glm::translate(PositionMatrix, -Location);

    glm::mat4 ViewMatrix = glm::transpose(VectorMatrix) * PositionMatrix;
    return ViewMatrix;
}

glm::vec3 Camera::GetLocation() const 
{
    return Location;
}