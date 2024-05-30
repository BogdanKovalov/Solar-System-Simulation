#include "Game.h"
#include "Window.h"
#include "InputSystem/InputAction.h"
#include "InputSystem/InputManager.h"
#include "Controller.h"
#include "Models/RenderSystem.h"
#include "Systems/Tick/TickSystem.h"
#include "Systems/SystemManager.h"
#include "ShaderManager.h"
#include "Pawn.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::shared_ptr<Game> Game::API;

std::shared_ptr<Game> Game::GetAPI()
{
    return API;
}

Game::Game()
{
    API = std::shared_ptr<Game>(this);
    MainInputManager = std::make_shared<InputManager>();
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

    MyWorld = std::make_shared<World>();
    auto NewController = std::make_shared<Controller>();
    MainWindow->SetController(NewController);
    Pawn* CreatedPawn = static_cast<Pawn*>(CreateEntity<Pawn>());
    NewController->SetPawn(std::shared_ptr<Pawn>(CreatedPawn));
    
    FObjectInitializer SystemInitializer;
    SystemInitializer.OwningWorld = MyWorld;
    SystemsManager = std::make_shared<SystemManager>(SystemInitializer);
    
    ShadersManager = std::shared_ptr<ShaderManager>(static_cast<ShaderManager*>(CreateEntity<ShaderManager>()));
 
}

void Game::CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share)
{
    MainWindow = std::make_shared<Window>(Width, Height, Title, Monitor, Share);
    
    glfwMakeContextCurrent(MainWindow->GetGLWindow());
    glfwSetKeyCallback(MainWindow->GetGLWindow(), GLProcessKeyboard);
    glfwSetCursorPosCallback(MainWindow->GetGLWindow(), GLProcessMouseMotion);
}

void Game::GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (!API)
    {
        return;
    }
    API->ProcessKeyboard(Key, Scancode, Action, Mods);
}

void Game::GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos)
{
    if (!API)
    {
        return;
    }
    API->ProcessMouseMotion(XPos, YPos);
}

void Game::ProcessKeyboard(int Key, int Scancode, int Action, int Mods)
{
    if (!MainInputManager)
    {
        return;
    }
    MainInputManager->ProcessKeyboard(Key, Scancode, Action, Mods);
}

void Game::ProcessMouseMotion(double XPos, double YPos) 
{
    if (!MainInputManager)
    {
        return;
    }
    MainInputManager->ProcessMouseMotion(XPos, YPos);
}


void Game::Tick(float DeltaTime) 
{
    SystemsManager->Update(DeltaTime);
}