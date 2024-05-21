#pragma once
#ifndef _ISYSTEM_H_
#define _ISYSTEM_H_

#include <memory>
class World;

class ISystem
{
public:
    virtual void Update(float DeltaTime) = 0;

    inline void SetOwningWorld(std::shared_ptr<World> NewWorld) { OwningWorld = NewWorld; }

protected:
    std::shared_ptr<World> OwningWorld;
};

#endif  // !_ISYSTEM_H_
