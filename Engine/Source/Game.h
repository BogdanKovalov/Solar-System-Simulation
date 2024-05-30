#pragma once
#ifndef _Game_H_
#define _Game_H_

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <ECS/World.h>
#include <ECS/Entity.h>
#include <Systems/ISystem.h>

class Window;
class TickObject;
class InputManager;
class SystemManager;
class ShaderManager;
struct GLFWwindow;
struct GLFWmonitor;

struct FObjectInitializer
{
    std::shared_ptr<World> OwningWorld;
    EntityID ID;
};

class Game
{
public:
    Game();

    void CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share);

    virtual void Tick(float DeltaTime);

    static std::shared_ptr<Game> GetAPI();
    std::shared_ptr<World> GetWorld() const { return MyWorld; }
    inline Window* GetWindow() const { return MainWindow.get(); }
    virtual inline glm::vec3 GetWorldUp() const { return WorldUp; }
    inline std::shared_ptr<InputManager> GetInputManger() { return MainInputManager; }

    // if we need to change WorldUp vector in other API
    void SetWorldUp(glm::vec3 NewWorldUp) { WorldUp = NewWorldUp; }
    void AddTickObject(TickObject* Object);

    static void GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
    static void GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos);

protected:
    void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    void ProcessMouseMotion(double XPos, double YPos);

    template <typename EntityClass>
    Entity* CreateEntity();

private:
    std::shared_ptr<InputManager> MainInputManager;
    std::shared_ptr<Window> MainWindow;
    std::shared_ptr<World> MyWorld;
    std::shared_ptr<SystemManager> SystemsManager;
    std::shared_ptr<ShaderManager> ShadersManager;

    glm::vec3 WorldUp;

    static std::shared_ptr<Game> API;
};

template <typename EntityClass>
inline Entity* Game::CreateEntity()
{
    static_assert(std::is_base_of<Entity, EntityClass>::value, "Only Entity childs allowed!");

    FObjectInitializer Initializer;
    Initializer.OwningWorld = MyWorld;
    Initializer.ID = MyWorld->CreateEntity();

    Entity* CreatedEntity = new EntityClass(Initializer);
    return CreatedEntity;
}

#endif