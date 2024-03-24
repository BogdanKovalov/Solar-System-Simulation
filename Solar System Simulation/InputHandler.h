#pragma once
#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <map>
#include <utility>
#include <functional>

#include "Types.h"

class InputHandler
{
public:
    void Bind(EKey KeyToBind, ETriggerEvent TriggerEvent, std::function<void()> CallToBind);

    void InputTriggered(EKey PressedKey, ETriggerEvent TriggerEvent) const;

    inline void DisableInput() { IsInputEnable = false; }

private:
    std::map<std::pair<EKey, ETriggerEvent>, std::function<void()>> KeyFunctionMap;

    bool IsInputEnable = true;
};

#endif  // !_INPUT_HANDLER_H_
