#include "Controller.h"
#include "InputSystem/InputHandler.h"
#include "InputSystem/InputAction.h"
#include "Game.h"
#include "Pawn.h"

#include <iostream>

Controller::Controller()
{
    InputComponent = std::make_shared<InputHandler>();
    MoveAction = std::make_shared<InputAction>();
    LookAction = std::make_shared<InputAction>();
    SetupInput();
}

void Controller::SetupInput()
{
    if (!InputComponent)
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