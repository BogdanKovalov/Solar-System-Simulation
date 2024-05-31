#include "Pawn.h"
#include "Camera.h"
#include "InputSystem/InputHandler.h"
#include "Game.h"
#include "ECS/World.h"
#include "Systems/Tick/TickSystem.h"
#include <functional>

#include <glm/gtc/matrix_transform.hpp>

Pawn::Pawn(FObjectInitializer const& Initializer) : Entity(Initializer)
{
    PawnTickComponent = std::shared_ptr<TickComponent>(dynamic_cast<TickComponent*>(AddComponent<TickComponent>()));
    PosComponent = std::shared_ptr<PositionComponent>(dynamic_cast<PositionComponent*>(AddComponent<PositionComponent>()));
    PawnCameraComponent = std::shared_ptr<CameraComponent>(dynamic_cast<CameraComponent*>(AddComponent<CameraComponent>()));
    PawnCameraComponent->PosComponent->Location = glm::vec3(0.0f);
    PosComponent->Location = glm::vec3(0.0f, 0.0f, 0.0f);

    if (PawnTickComponent)
    {
        PawnTickComponent->TickFunction = std::bind(&Pawn::Tick, this, std::placeholders::_1);
    }
}

void Pawn::Tick(float DeltaTime)
{
    AddOffset(Velocity * DeltaTime);
}

inline void Pawn::AddOffset(glm::vec3 Offset)
{
    PosComponent->Location += Offset;
    PawnCameraComponent->PosComponent->Location += Offset;
}

void Pawn::Rotate(glm::vec2 YawAndPitch)
{
    if (!PawnCameraComponent)
    {
        return;
    }

    glm::mat4 RotaionMatrix(1.0f);
    RotaionMatrix = glm::rotate(RotaionMatrix, glm::radians(YawAndPitch.x), GetUpVector());
    RotaionMatrix = glm::rotate(RotaionMatrix, glm::radians(YawAndPitch.y), GetRightVector());

    Velocity = RotaionMatrix * glm::vec4(Velocity, 1.0f);

    auto CameraPosition = PawnCameraComponent->PosComponent;
    CameraPosition->Rotation += glm::vec3(YawAndPitch, 0.0f);
    if (CameraPosition->Rotation.y >= 90.0f)
    {
        CameraPosition->Rotation.y = 89.9f;
    }
    if (CameraPosition->Rotation.y <= -90.0f)
    {
        CameraPosition->Rotation.y = -89.9f;
    }

    PawnCameraComponent->ForwardVector.z = cos(glm::radians(CameraPosition->Rotation.x)) * cos(glm::radians(CameraPosition->Rotation.y));
    PawnCameraComponent->ForwardVector.y = sin(glm::radians(CameraPosition->Rotation.y));
    PawnCameraComponent->ForwardVector.x = sin(glm::radians(CameraPosition->Rotation.x)) * cos(glm::radians(CameraPosition->Rotation.y));

    PawnCameraComponent->ForwardVector = glm::normalize(PawnCameraComponent->ForwardVector);
    PawnCameraComponent->RightVector = glm::normalize(glm::cross(PawnCameraComponent->ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));
    PawnCameraComponent->UpVector = glm::cross(PawnCameraComponent->RightVector, PawnCameraComponent->ForwardVector);
}

glm::vec3 Pawn::GetForwardVector() const
{
    if (!PawnCameraComponent)
    {
        return glm::vec3();
    }
    return PawnCameraComponent->ForwardVector;
}

glm::vec3 Pawn::GetRightVector() const
{
    if (!PawnCameraComponent)
    {
        return glm::vec3();
    }
    return PawnCameraComponent->RightVector;
}

glm::vec3 Pawn::GetUpVector() const
{
    if (!PawnCameraComponent)
    {
        return glm::vec3();
    }
    return PawnCameraComponent->UpVector;
}