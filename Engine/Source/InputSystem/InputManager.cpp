#include "InputManager.h"
#include "../Types.h"
#include "InputAction.h"

void InputManager::AddInputAction(InputAction* Action) 
{
    InputActions.push_back(Action);
}

void InputManager::ProcessKeyboard(int Key, int Scancode, int Action, int Mods) 
{
    for (auto IAction : InputActions)
    {
        if (!IAction)
        {
            continue;
        }
        IAction->SetInputValue(static_cast<ETrigger>(Key), static_cast<ETriggerEvent>(Action));
    }
}

void InputManager::ProcessMouseMotion(double XPos, double YPos)
{
    for (auto IAction : InputActions)
    {
        if (!IAction)
        {
            continue;
        }
        if (IAction->IsRespondingToInput(ETrigger::MOUSEMOVE, ETriggerEvent::TRIGGERED))
        {
            IAction->SetInputValue(glm::vec3(XPos, YPos, 0.0f));
        }
    }
}