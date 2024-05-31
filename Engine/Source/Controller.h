#pragma once
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <memory>
#include <glm/glm.hpp>
#include "Types.h"

class InputHandler;
class Pawn;
struct GLFWwindow;
class InputAction;

class Controller
{
public:
    Controller();

    inline void SetPawn(std::shared_ptr<Pawn> NewPawn) { ControlledPawn = NewPawn; }

    void Move(FInputValue const& InputValue);
    void Look(FInputValue const& InputValue);

protected:
    virtual void SetupInput();

private:
    std::shared_ptr<InputHandler> InputComponent;
    std::shared_ptr<Pawn> ControlledPawn;

    std::shared_ptr<InputAction> MoveAction;
    std::shared_ptr<InputAction> LookAction;

    glm::vec2 LastMousePos;
    float MouseSensitivity = 0.01f;
    bool FirstMouse = true;
};

#endif