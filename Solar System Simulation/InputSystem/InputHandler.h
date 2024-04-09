#pragma once
#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <map>
#include <utility>
#include <memory>
#include <functional>

#include "Types.h"
#include "InputAction.h"

class InputAction;

class InputHandler
{
public:
    template<class Function, class ... Args>
    void Bind(std::shared_ptr<InputAction> Action, Function&& FunctionToCall, Args&&... Arguements);

    void InputTriggered(InputAction* Action) const;

    inline void DisableInput() { IsInputEnable = false; }

private:
    std::map<InputAction*, std::function<void(FInputValue const&)>> KeyFunctionMap;

    bool IsInputEnable = true;
};

template <class Function, class... Args>
inline void InputHandler::Bind(std::shared_ptr<InputAction> Action, Function&& FunctionToCall, Args&&... Arguements)
{
    if (!Action)
    {
        return;
    }
    //Action->SetInputHandler(std::shared_ptr<InputHandler>(this));
    auto Functor = std::bind(std::forward<Function>(FunctionToCall), std::forward<Args>(Arguements)...);
    KeyFunctionMap.emplace(Action.get(), Functor);
}

#endif  // !_INPUT_HANDLER_H_
