#include "InputAction.h"
#include "InputManager.h"
#include "../Aplication.h"

InputAction::InputAction() 
{
    auto API = Aplication::GetAPI();
    if (API)
    {
        if (auto MainInputManager = API->GetInputManger())
        {
            MainInputManager->AddInputAction(this);
        }
    }
}

void InputAction::AddTrigger(ETrigger Trigger, ETriggerEvent Event, EAxes TriggerAxis, float Modifier)
{
    AddTrigger(std::make_pair(Trigger, Event), TriggerAxis, Modifier);
}

void InputAction::AddTrigger(std::pair<ETrigger, ETriggerEvent> Triggers, EAxes TriggerAxis, float Modifier)
{
    TriggersAxisMap.emplace(std::make_pair(Triggers, std::make_pair(TriggerAxis, Modifier)));
}

void InputAction::SetInputValue(glm::vec3 NewInputValue)
{
    CurrentInputValue.Set(NewInputValue);
    if (BindedFunction)
    {
        BindedFunction(CurrentInputValue);
    }
}

void InputAction::SetInputValue(ETrigger Trigger, ETriggerEvent Event)
{
    auto Found = TriggersAxisMap.find(std::make_pair(Trigger, Event));
    if (Found == TriggersAxisMap.end())
    {
        return;
    }
    CurrentInputValue.GetAxisValue(Found->second.first) = static_cast<float>(Event) * Found->second.second;

    if (BindedFunction)
    {
        BindedFunction(CurrentInputValue);
    }
}

bool InputAction::IsRespondingToInput(ETrigger Trigger, ETriggerEvent Event) const
{
    auto Found = TriggersAxisMap.find(std::make_pair(Trigger, Event));
    if (Found == TriggersAxisMap.end())
    {
        return false;
    }
    return true;
}
