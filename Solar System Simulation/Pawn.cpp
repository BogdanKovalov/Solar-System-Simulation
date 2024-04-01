#include "Pawn.h"
#include "Camera.h"
#include "InputHandler.h"

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
    return AttachedCamera->GetViewMatrix();
}