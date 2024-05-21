#pragma once
#ifndef _APLICATION_H_
#define _APLICATION_H_

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <ECS/World.h>
#include <Systems/ISystem.h>

class Window;
class TickObject;
class InputManager;
struct GLFWwindow;
struct GLFWmonitor;

struct FObjectInitializer
{
    std::shared_ptr<World> OwningWorld;
    EntityID ID;
};

class Aplication
{
public:
    Aplication();

    void CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share);

    virtual void Tick(float DeltaTime);

    static std::shared_ptr<Aplication> GetAPI();
    std::shared_ptr<World> GetWorld() const { return MyWorld; }
    inline Window* GetWindow() const { return MainWindow.get(); }
    virtual inline glm::vec3 GetWorldUp() const { return WorldUp; }
    inline std::shared_ptr<InputManager> GetInputManger() { return MainInputManager; }

    // if we need to change WorldUp vector in other API
    void SetWorldUp(glm::vec3 NewWorldUp) { WorldUp = NewWorldUp; }
    void AddTickObject(TickObject* Object);

    static void GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
    static void GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos);

    void InitializeSystems();

protected:
    void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    void ProcessMouseMotion(double XPos, double YPos);

    template <typename EntityClass>
    Entity* CreateEntity();

private:
    std::shared_ptr<InputManager> MainInputManager;
    std::shared_ptr<Window> MainWindow;
    std::vector<TickObject*> TickObjects;

    std::shared_ptr<World> MyWorld;

    std::vector<Entity*> Entitites;
    std::vector<std::shared_ptr<ISystem>> Systems;

    glm::vec3 WorldUp;

    static std::shared_ptr<Aplication> API;
};

//#include "Pawn.h"

template <typename EntityClass>
inline Entity* Aplication::CreateEntity()
{
    static_assert(std::is_base_of<Entity, EntityClass>::value, "Only Entity childs allowed!");

    FObjectInitializer Initializer;
    Initializer.OwningWorld = MyWorld;
    Initializer.ID = MyWorld->CreateEntity();

    Entity* CreatedEntity = new EntityClass(Initializer);
    //Entitites.push_back(dynamic_cast<Entity*>(CreatedEntity));
    return CreatedEntity;
}

#endif