#pragma once
#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include "ECS/World.h"
#include "Systems/ISystem.h"

class RenderSystem : public ISystem
{
public:
    virtual void Update(float DeltaTime) override;
};

#endif
