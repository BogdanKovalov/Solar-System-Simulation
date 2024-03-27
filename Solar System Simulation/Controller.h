#pragma once
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <memory>
#include <glm/glm.hpp>

class InputHandler;
class Pawn;
class GLFWwindow;

class Controller
{
public:
    Controller();
    void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    void ProcessMouseMotion(double XPos, double YPos);
    
    glm::mat4 GetView() const;

private:
    std::shared_ptr<InputHandler> InputComponent;
    std::shared_ptr<Pawn> ControlledPawn;
};

#endif