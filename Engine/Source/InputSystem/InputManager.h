#pragma once
#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <vector>

class InputAction;

class InputManager
{
public:
    void AddInputAction(InputAction* Action);

    virtual void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    virtual void ProcessMouseMotion(double XPos, double YPos);

private:
    std::vector<InputAction*> InputActions;
};

#endif