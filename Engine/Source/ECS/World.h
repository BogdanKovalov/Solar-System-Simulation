#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <boost/functional/hash.hpp>

struct ArchetypeRecord;
struct Archetype;

typedef unsigned long long EntityID;
typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;
typedef unsigned int ArchetypeID;
typedef size_t ComponentID;
typedef std::vector<ComponentID> ArchetypeType;
typedef std::unordered_set<ArchetypeID> ArchetypeSet;
typedef std::unordered_map<ArchetypeID, std::shared_ptr<ArchetypeRecord>> ArchetypeMap;

template <typename Container>
struct ContainerHash
{
    std::size_t operator()(Container const& C) const { return boost::hash_range(C.begin(), C.end()); }
};

struct Component
{
public:
    virtual void DummyFunction(){};
};

struct PositionComponent : public Component
{
public:
    int x;
    int y;
    int z;
};

class Entity
{
private:
    EntityID ID;
    std::vector<ComponentID> Components;
};

struct Archetype
{
    Archetype()
    {
        static ArchetypeID GlobalID = 0;
        ID = GlobalID++;
        std::cout << GlobalID << std::endl;
    };
    ArchetypeID ID;
    ArchetypeType Type;
    std::vector<std::vector<Component*>> Components;
    std::unordered_map<ComponentID, std::shared_ptr<Archetype>> AddArchetypes;
};

struct Record
{
public:
    Record() : RecordArchetype(new Archetype), Row(0){};
    std::shared_ptr<Archetype> RecordArchetype;
    size_t Row;
};

struct ArchetypeRecord
{
    size_t Column;
};

class World
{
public:
    EntityID CreateEntity();

    void DestroyEntity(EntityID ID);

    template <class ComponentType>
    void AddComponent(EntityID Entity);

    template <class ComponentType>
    ComponentType* GetComponent(EntityID Entity);

    template <class ComponentType>
    std::vector<ComponentType*>& GetAllComponents();

    template <class ComponentType>
    bool HasComponent(EntityID Entity);

    template <class ComponentType>
    ComponentID GetComponentID();

private:
    std::vector<EntityID> Entities;
    std::vector<EntityID> FreeEntities;

    std::unordered_map<ArchetypeType, std::shared_ptr<Archetype>, ContainerHash<ArchetypeType>> ArchetypeTypeMap;
    std::unordered_map<EntityID, std::shared_ptr<Record>> EntityRecordMap;
    std::unordered_map<ComponentID, ArchetypeMap> ComponentArchetypesMap;

private:
    EntityID CreateEntityID(EntityIndex Index, EntityVersion Version) { return ((EntityID)Index << 32) | ((EntityID)Version); }

    EntityVersion GetEntityVersion(EntityID Index) { return (EntityVersion)Index; }
    EntityIndex GetEntityIndex(EntityID ID) { return ID >> 32; }

    // This is template function, because Entity can be moved to another archetype, if new component added
    template <class ComponentType>
    void MoveEntityToArchetype(EntityID ID, std::shared_ptr<Archetype> NewArcehtype);
    std::vector<Component*> MoveComponentsToArcehtype(std::vector<Component*>& Components, std::shared_ptr<Archetype> DestinationArchetype);
};

template <class ComponentType>
inline void World::AddComponent(EntityID Entity)
{
    if (EntityRecordMap.find(Entity) == EntityRecordMap.end())
    {
        EntityRecordMap.emplace(Entity, std::shared_ptr<Record>(new Record));
    }
    std::shared_ptr<Record> FoundRecord = EntityRecordMap[Entity];
    std::shared_ptr<Archetype> SourceArchetype = FoundRecord->RecordArchetype;

    ComponentID CompID = GetComponentID<ComponentType>();
    ArchetypeType NewType = SourceArchetype->Type;
    if (std::find(NewType.begin(), NewType.end(), CompID) != NewType.end())
    {
        return;
    }
    NewType.push_back(CompID);
    if (ArchetypeTypeMap.find(NewType) == ArchetypeTypeMap.end())
    {
        ArchetypeTypeMap.emplace(NewType, std::shared_ptr<Archetype>(new Archetype));
    }
    std::shared_ptr<Archetype> DestinationArchetype = ArchetypeTypeMap[NewType];

    if (SourceArchetype->AddArchetypes.find(CompID) == SourceArchetype->AddArchetypes.end())
    {
        SourceArchetype->AddArchetypes.emplace(CompID, DestinationArchetype);
    }

    MoveEntityToArchetype<ComponentType>(Entity, DestinationArchetype);
}

template <class ComponentType>
inline ComponentType* World::GetComponent(EntityID Entity)
{
    std::shared_ptr<Record> FoundRecord = EntityRecordMap[Entity];
    std::shared_ptr<Archetype> FoundArchetype = FoundRecord->RecordArchetype;

    ComponentID CompID = GetComponentID<ComponentType>();
    ArchetypeMap& Archetypes = ComponentArchetypesMap[CompID];
    if (Archetypes.count(FoundArchetype->ID) == 0)
    {
        return nullptr;
    }

    std::shared_ptr<ArchetypeRecord> FoundArchetypeRecord = Archetypes[FoundArchetype->ID];
    return static_cast<ComponentType*>(FoundArchetype->Components[FoundRecord->Row][FoundArchetypeRecord->Column]);
}

template <class ComponentType>
inline std::vector<ComponentType*>& World::GetAllComponents()
{
    ComponentID CompID = GetComponentID<ComponentType>();
    ArchetypeMap& Archetypes = ComponentArchetypesMap[CompID];
}

template <class ComponentType>
inline bool World::HasComponent(EntityID Entity)
{
    std::shared_ptr<Record> FoundRecord = EntityRecordMap[Entity];
    std::shared_ptr<Archetype> FoundArchetype = FoundRecord->RecordArchetype;

    ComponentID CompID = GetComponentID<ComponentType>();
    ArchetypeMap& Archetypes = ComponentArchetypesMap[CompID];
    return Archetypes.count(FoundArchetype->ID) != 0;
}

template <class ComponentType>
inline ComponentID World::GetComponentID()
{
    return typeid(ComponentType).hash_code();
}

template <class ComponentType>
inline void World::MoveEntityToArchetype(EntityID ID, std::shared_ptr<Archetype> NewArcehtype)
{
    if (EntityRecordMap.find(ID) == EntityRecordMap.end())
    {
        EntityRecordMap.emplace(ID, std::shared_ptr<Record>(new Record));
    }
    std::shared_ptr<Record> FoundRecord = EntityRecordMap[ID];
    std::shared_ptr<Archetype> SourceArchetype = FoundRecord->RecordArchetype;

    ComponentID CompID = GetComponentID<ComponentType>();
    std::vector<Component*> NewColumn;
    if (SourceArchetype->Components.size() != 0)
    {
        NewColumn = MoveComponentsToArcehtype(SourceArchetype->Components[FoundRecord->Row], NewArcehtype);
    }
    NewColumn.push_back(new ComponentType());
    NewArcehtype->Components.push_back(NewColumn);
    FoundRecord->RecordArchetype = NewArcehtype;
    FoundRecord->Row = NewArcehtype->Components.size() - 1;

    ArchetypeMap& Archetypes = ComponentArchetypesMap[CompID];
    if (Archetypes.find(NewArcehtype->ID) == Archetypes.end())
    {
        Archetypes.emplace(NewArcehtype->ID, std::shared_ptr<ArchetypeRecord>(new ArchetypeRecord));
    }
    std::shared_ptr<ArchetypeRecord> Record = Archetypes[NewArcehtype->ID];
    Record->Column = NewColumn.size() - 1;
}

#endif  // !_WORLD_H_