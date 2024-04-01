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
    void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    void ProcessMouseMotion(double XPos, double YPos);

    glm::mat4 GetView() const;

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

    bool FirstMouse = true;
};

#endif