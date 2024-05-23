#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <memory>
#include <vector>
#include "ECS/World.h"

struct FObjectInitializer;
struct Component;
class World;

typedef unsigned long long EntityID;
typedef size_t ComponentID;

class Entity
{
public:
    Entity() = delete;
    Entity(FObjectInitializer const& Initializer);
    template <typename ComponentType>
    Component* AddComponent();

protected:
    EntityID ID;
    std::shared_ptr<World> OwningWorld;
    std::vector<ComponentID> Components;
};

template <typename ComponentType>
inline Component* Entity::AddComponent()
{
    if (!OwningWorld)
    {
        return nullptr;
    }
    return OwningWorld->AddComponent<ComponentType>(ID);
}

#endif  // !_ENTITY_H_