#include "SystemManager.h"
#include "ECS/World.h"
#include "Systems/ISystem.h"
#include "Models/RenderSystem.h"
#include "Systems/Tick/TickSystem.h"
#include "Game.h"

SystemManager::SystemManager(FObjectInitializer const& Initializer)
{
    OwningWorld = Initializer.OwningWorld;
    InitializeSystems();
}

void SystemManager::InitializeSystems() 
{
    Systems.push_back(std::make_shared<RenderSystem>());
    Systems.push_back(std::make_shared<TickSystem>());

    for (auto System : Systems)
    {
        System->SetOwningWorld(OwningWorld);
    }
}

void SystemManager::Update(float DeltaTime) 
{
    for (auto System : Systems)
    {
        if (System)
        {
            System->Update(DeltaTime);
        }
    }
}