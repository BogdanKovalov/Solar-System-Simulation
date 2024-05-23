#pragma once
#ifndef _SYSTEM_MANAGER_H_
#define _SYSTEM_MANAGER_H_

#include <vector>
#include <memory>

class ISystem;
class World;
struct FObjectInitializer;

class SystemManager
{
public:
    SystemManager(FObjectInitializer const& Initializer);
    SystemManager() = delete;
    SystemManager(SystemManager const& OtherManager) = delete;
    SystemManager(SystemManager&& OtherManager) = delete;
    SystemManager* operator=(SystemManager const& OtherManager) = delete;
    SystemManager* operator=(SystemManager&& OtherManager) = delete;

    void Update(float DeltaTime);

protected:
    std::vector<std::shared_ptr<ISystem>> Systems;
    std::shared_ptr<World> OwningWorld;

    private:
    void InitializeSystems();
};

#endif