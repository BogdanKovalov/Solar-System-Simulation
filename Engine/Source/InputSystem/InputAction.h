#pragma once
#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

#include "../Types.h"
#include <map>
#include <memory>
#include <functional>

class InputHandler;

class InputAction
{
public:
    InputAction();

    void AddTrigger(ETrigger Trigger, ETriggerEvent Event, EAxes TriggerAxis = EAxes::X, float Modifier = 1);
    void AddTrigger(std::pair<ETrigger, ETriggerEvent> Triggers, EAxes TriggerAxis = EAxes::X, float Modifier = 1);

    void SetInputValue(glm::vec3 NewInputValue);
    void SetInputValue(ETrigger Trigger, ETriggerEvent Event);

     template <class Function, class... Args>
    void Bind(Function&& FunctionToCall, Args&&... Arguements);

    bool IsRespondingToInput(ETrigger Trigger, ETriggerEvent Event) const;
    FInputValue GetInputValue() const { return CurrentInputValue; }

private:
    std::function<void(FInputValue const&)> BindedFunction;
    std::map<std::pair<ETrigger, ETriggerEvent>, std::pair<EAxes, float>> TriggersAxisMap;
    FInputValue CurrentInputValue;
};

template <class Function, class... Args>
inline void InputAction::Bind(Function&& FunctionToCall, Args&&... Arguements)
{
    BindedFunction = std::bind(std::forward<Function>(FunctionToCall), std::forward<Args>(Arguements)...);
}

#endif  // !_INPUT_ACTION_H_
