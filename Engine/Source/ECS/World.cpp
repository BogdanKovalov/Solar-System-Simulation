#include "World.h"

EntityID World::CreateEntity()
{
    if (!FreeEntities.empty())
    {
        EntityIndex NewIndex = GetEntityIndex(FreeEntities.back());
        FreeEntities.pop_back();
        EntityID NewID = CreateEntityID(NewIndex, GetEntityVersion(Entities[NewIndex]));
        Entities[NewIndex] = NewID;
        return NewID;
    }
    Entities.push_back(CreateEntityID(Entities.size(), 0));
    return Entities.back();
}

void World::DestroyEntity(EntityID ID)
{
    EntityID NewID = CreateEntityID(EntityIndex(-1), GetEntityVersion(ID) + 1);
    Entities[GetEntityIndex(ID)] = NewID;
    FreeEntities.push_back(ID);
}

std::vector<Component*> World::MoveComponentsToArcehtype(
    std::vector<Component*>& Components, std::shared_ptr<Archetype> DestinationArchetype)
{
    std::vector<Component*> NewColumn = Components;
    Components.clear();
    for (int i = 0; i < NewColumn.size(); ++i)
    {
        ArchetypeMap& Archetypes = ComponentArchetypesMap[typeid(*NewColumn[i]).hash_code()];
        if (Archetypes.find(DestinationArchetype->ID) == Archetypes.end())
        {
            Archetypes.emplace(DestinationArchetype->ID, std::shared_ptr<ArchetypeRecord>(new ArchetypeRecord));
        }
        std::shared_ptr<ArchetypeRecord> Record = Archetypes[DestinationArchetype->ID];
        Record->Column = i;
    }
    return NewColumn;
}
