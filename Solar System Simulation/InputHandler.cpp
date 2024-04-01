#include "InputHandler.h"
#include "Types.h"
#include "glm/glm.hpp"

/* void InputHandler::Bind(ETrigger Trigger, ETriggerEvent TriggerEvent, std::function<void(FInputValue const&)> CallToBind)
{
    KeyFunctionMap.emplace(std::make_pair(std::make_pair(Trigger, TriggerEvent), CallToBind));
}*/



void InputHandler::InputTriggered(InputAction* Action) const 
{
    if (!IsInputEnable || !Action)
    {
        return;
    }
    auto KeyFunctionPair = KeyFunctionMap.find(Action);
    if (KeyFunctionPair == KeyFunctionMap.end())
    {
        return;
    }

    KeyFunctionPair->second(Action->GetInputValue());
}