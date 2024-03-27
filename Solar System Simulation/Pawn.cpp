#include "Pawn.h"
#include "Camera.h"
#include "InputHandler.h"

Pawn::Pawn(glm::vec3 Location, glm::vec3 Velocity)
{
    this->Location = Location;
    this->Velocity = Velocity;

    AttachedCamera = std::shared_ptr<Camera>(new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
}

void Pawn::SetupInput(std::shared_ptr<InputHandler> InputComponent)
{
    if (!InputComponent)
    {
        return;
    }
    InputComponent->Bind(
        EKey::W, ETriggerEvent::PRESSED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetForwardVector() * 1.0f));
    InputComponent->Bind(EKey::W, ETriggerEvent::RELEASED,
        std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetForwardVector() * -1.0f));

    InputComponent->Bind(
        EKey::S, ETriggerEvent::PRESSED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetForwardVector() * -1.0f));
    InputComponent->Bind(
        EKey::S, ETriggerEvent::RELEASED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetForwardVector() * 1.0f));

    InputComponent->Bind(
        EKey::D, ETriggerEvent::PRESSED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetRightVector() * 1.0f));
    InputComponent->Bind(
        EKey::D, ETriggerEvent::RELEASED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetRightVector() * -1.0f));

    InputComponent->Bind(
        EKey::A, ETriggerEvent::PRESSED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetRightVector() * -1.0f));
    InputComponent->Bind(
        EKey::A, ETriggerEvent::RELEASED, std::bind(&Camera::AddVelocity, AttachedCamera.get(), AttachedCamera->GetRightVector() * 1.0f));
}

glm::mat4 Pawn::GetView() const
{
    return AttachedCamera->GetViewMatrix();
}