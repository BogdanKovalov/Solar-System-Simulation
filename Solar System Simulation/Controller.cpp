#include "Controller.h"
#include "InputHandler.h"
#include "InputAction.h"
#include "Aplication.h"
#include "Pawn.h"

#include <iostream>

Controller::Controller()
{
    InputComponent = std::shared_ptr<InputHandler>(new InputHandler());
    ControlledPawn = std::shared_ptr<Pawn>(new Pawn(glm::vec3(0.0f, 0.0f, -3.0f)));
    MoveAction = std::shared_ptr<InputAction>(new InputAction());
    LookAction = std::shared_ptr<InputAction>(new InputAction());
    SetupInput();
}

void Controller::ProcessKeyboard(int Key, int Scancode, int Action, int Mods)
{
    //InputComponent->InputTriggered(static_cast<ETrigger>(Key), static_cast<ETriggerEvent>(Action));
}

void Controller::ProcessMouseMotion(double XPos, double YPos) {}

void Controller::SetupInput()
{
    if (!InputComponent || !ControlledPawn)
    {
        return;
    }
    MoveAction->AddTrigger(ETrigger::W, ETriggerEvent::PRESSED, EAxes::X);
    MoveAction->AddTrigger(ETrigger::A, ETriggerEvent::PRESSED, EAxes::Y, -1.0f);
    MoveAction->AddTrigger(ETrigger::S, ETriggerEvent::PRESSED, EAxes::X, -1.0f);
    MoveAction->AddTrigger(ETrigger::D, ETriggerEvent::PRESSED, EAxes::Y);
    MoveAction->AddTrigger(ETrigger::W, ETriggerEvent::RELEASED, EAxes::X);
    MoveAction->AddTrigger(ETrigger::A, ETriggerEvent::RELEASED, EAxes::Y);
    MoveAction->AddTrigger(ETrigger::S, ETriggerEvent::RELEASED, EAxes::X);
    MoveAction->AddTrigger(ETrigger::D, ETriggerEvent::RELEASED, EAxes::Y);
    MoveAction->Bind(&Controller::Move, this, std::placeholders::_1);

    LookAction->AddTrigger(ETrigger::MOUSEMOVE, ETriggerEvent::TRIGGERED);
    LookAction->Bind(&Controller::Look, this, std::placeholders::_1);
}

void Controller::Move(FInputValue const& InputValue)
{
    if (!ControlledPawn)
    {
        return;
    }
    glm::vec2 Value = InputValue.Get<glm::vec2>();

    glm::vec3 VelocityX = ControlledPawn->GetForwardVector() * Value.x;
    glm::vec3 VelocityY = ControlledPawn->GetRightVector() * Value.y;
    ControlledPawn->SetVelocity(VelocityX + VelocityY);
}

void Controller::Look(FInputValue const& InputValue) 
{
    if (!ControlledPawn || FirstMouse)
    {
        FirstMouse = false;
        LastMousePos = InputValue.Get<glm::vec2>();
        return;
    }
    glm::vec2 DeltaMouse = InputValue.Get<glm::vec2>() - LastMousePos;
    LastMousePos = InputValue.Get<glm::vec2>();
    ControlledPawn->Rotate(DeltaMouse * MouseSensitivity);
}

glm::mat4 Controller::GetView() const
{
    if (!ControlledPawn)
    {
        return glm::mat4();
    }
    return ControlledPawn->GetView();
}

glm::vec3 Controller::GetCameraLocation() const
{
    if (!ControlledPawn)
    {
        return glm::vec3();
    }
    return ControlledPawn->GetCameraLocation();
}