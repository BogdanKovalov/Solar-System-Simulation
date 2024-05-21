#include "TickSystem.h"

void TickSystem::Update(float DeltaTime)
{
    if (!OwningWorld)
    {
        return;
    }

    std::vector<TickComponent*> TickComponents = OwningWorld->GetAllComponents<TickComponent>();
    for (auto TickComponent : TickComponents)
    {
        if (TickComponent->TickFunction)
        {
            TickComponent->TickFunction(DeltaTime);
        }
    }
}
