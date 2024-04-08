#include "Pawn.h"
#include "Camera.h"
#include "InputHandler.h"

#include <glm/gtc/matrix_transform.hpp>

Pawn::Pawn(glm::vec3 Location, glm::vec3 Velocity)
{
    this->Location = Location;
    this->Velocity = Velocity;

    AttachedCamera = std::shared_ptr<Camera>(new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
}

void Pawn::Tick(float DeltaTime) 
{
    AddOffset(Velocity * DeltaTime);
    AttachedCamera->AddOffset(Velocity * DeltaTime);
}

inline void Pawn::AddOffset(glm::vec3 Offset) 
{
    Location += Offset;
    AttachedCamera->AddOffset(Offset);
}

void Pawn::Rotate(glm::vec2 YawAndPitch) 
{
    if (!AttachedCamera)
    {
        return;
    }

    glm::mat4 RotaionMatrix(1.0f);
    RotaionMatrix = glm::rotate(RotaionMatrix, glm::radians(YawAndPitch.x), GetUpVector());
    RotaionMatrix = glm::rotate(RotaionMatrix, glm::radians(YawAndPitch.y), GetRightVector());

    Velocity = RotaionMatrix * glm::vec4(Velocity, 1.0f);

    AttachedCamera->Rotate(YawAndPitch);
}

glm::vec3 Pawn::GetForwardVector() const
{
    if (!AttachedCamera)
    {
        return glm::vec3();
    }
    return AttachedCamera->GetForwardVector();
}

glm::vec3 Pawn::GetRightVector() const
{
    if (!AttachedCamera)
    {
        return glm::vec3();
    }
    return AttachedCamera->GetRightVector();
}

glm::vec3 Pawn::GetUpVector() const
{
    if (!AttachedCamera)
    {
        return glm::vec3();
    }
    return AttachedCamera->GetUpVector();
}

glm::mat4 Pawn::GetView() const
{
    if (!AttachedCamera)
    {
        return glm::mat4();
    }
    return AttachedCamera->GetViewMatrix();
}

glm::vec3 Pawn::GetCameraLocation() const
{
    if (!AttachedCamera)
    {
        return glm::vec3();
    }
    return AttachedCamera->GetLocation();
}