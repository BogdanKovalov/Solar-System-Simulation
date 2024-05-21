#include "Aplication.h"
#include "Window.h"
#include "InputSystem/InputAction.h"
#include "InputSystem/InputManager.h"
#include "Controller.h"
#include "Models/RenderSystem.h"
#include "Systems/Tick/TickSystem.h"
#include "Pawn.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::shared_ptr<Aplication> Aplication::API;

std::shared_ptr<Aplication> Aplication::GetAPI()
{
    return API;
}

Aplication::Aplication()
{
    API = std::shared_ptr<Aplication>(this);
    MainInputManager = std::shared_ptr<InputManager>(new InputManager());
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    int Success = glfwInit();
    if (Success == GLFW_FALSE)
    {
        glfwTerminate();
        std::cout << "Failure";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    CreateWindow(1920, 1080, "Solar System Simulation", nullptr, nullptr);
    Success = glewInit();

    glfwSetInputMode(MainWindow->GetGLWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    MyWorld = std::shared_ptr<World>(new World);
    auto NewController = std::shared_ptr<Controller>(new Controller());
    MainWindow->SetController(NewController);
    Pawn* CreatedPawn = static_cast<Pawn*>(CreateEntity<Pawn>());
    NewController->SetPawn(std::shared_ptr<Pawn>(CreatedPawn));
    InitializeSystems();
}

void Aplication::CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share)
{
    MainWindow = std::shared_ptr<Window>(new Window(Width, Height, Title, Monitor, Share));
    
    glfwMakeContextCurrent(MainWindow->GetGLWindow());
    glfwSetKeyCallback(MainWindow->GetGLWindow(), GLProcessKeyboard);
    glfwSetCursorPosCallback(MainWindow->GetGLWindow(), GLProcessMouseMotion);
}

void Aplication::GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (!API)
    {
        return;
    }
    API->ProcessKeyboard(Key, Scancode, Action, Mods);
}

void Aplication::GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos)
{
    if (!API)
    {
        return;
    }
    API->ProcessMouseMotion(XPos, YPos);
}

void Aplication::ProcessKeyboard(int Key, int Scancode, int Action, int Mods)
{
    if (!MainInputManager)
    {
        return;
    }
    MainInputManager->ProcessKeyboard(Key, Scancode, Action, Mods);
}

void Aplication::ProcessMouseMotion(double XPos, double YPos) 
{
    if (!MainInputManager)
    {
        return;
    }
    MainInputManager->ProcessMouseMotion(XPos, YPos);
}

void Aplication::AddTickObject(TickObject* Object) 
{
    TickObjects.push_back(Object);
}


void Aplication::Tick(float DeltaTime) 
{
    for (auto System : Systems)
    {
        if (System)
        {
            System->Update(DeltaTime);
        }
    }
}

void Aplication::InitializeSystems() 
{
    Systems.push_back(std::shared_ptr<RenderSystem>(new RenderSystem));
    Systems.push_back(std::shared_ptr<TickSystem>(new TickSystem));

    for (auto System : Systems)
    {
        System->SetOwningWorld(MyWorld);
    }
}