#pragma once
#ifndef _TICK_SYSTEM_H_
#define _TICK_SYSTEM_H_

#include "Systems/ISystem.h"
#include "ECS/World.h"
#include <functional>

struct TickComponent : Component
{
public:
    std::function<void(float)> TickFunction;
};


class TickSystem : public ISystem
{
    virtual void Update(float DeltaTime) override;
};


#endif  // !_TICK_SYSTEM_H_
