#include "InputHandler.h"

void InputHandler::Bind(EKey KeyToBind, ETriggerEvent TriggerEvent, std::function<void()> CallToBind) 
{
    KeyFunctionMap.emplace(std::make_pair(std::make_pair(KeyToBind, TriggerEvent), CallToBind));
}

void InputHandler::InputTriggered(EKey PressedKey, ETriggerEvent TriggerEvent) const 
{
    if (!IsInputEnable)
    {
        return;
    }
    auto KeyFunctionPair = KeyFunctionMap.find(std::make_pair(PressedKey, TriggerEvent));
    if (KeyFunctionPair == KeyFunctionMap.end())
    {
        return;
    }

    KeyFunctionPair->second();
}