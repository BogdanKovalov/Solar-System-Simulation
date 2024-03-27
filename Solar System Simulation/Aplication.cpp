#include "Aplication.h"
#include "Window.h"
#include "TickObject.h"
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

    CreateWindow(1000, 1000, "Solar System Simulation", nullptr, nullptr);
    Success = glewInit();

}

void Aplication::CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share)
{
    MainWindow = std::shared_ptr<Window>(new Window(Width, Height, Title, Monitor, Share));
    
    glfwMakeContextCurrent(MainWindow->GetGLWindow());
    glfwSetKeyCallback(MainWindow->GetGLWindow(), GLProcessKeyboard);
}

void Aplication::GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (!API)
    {
        return;
    }
    API->ProcessKeyboard(Window, Key, Scancode, Action, Mods);
}

void Aplication::GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos)
{
    if (!API)
    {
        return;
    }
    API->ProcessMouseMotion(Window, XPos, YPos);
}

void Aplication::ProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (!Window && !MainWindow)
    {
        return;
    }
    if (Window == MainWindow->GetGLWindow())
    {
        MainWindow->ProcessKeyboard(Key, Scancode, Action, Mods);
    }
}

void Aplication::ProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos)
{
    if (!Window && !MainWindow)
    {
        return;
    }
    if (Window == MainWindow->GetGLWindow())
    {
        MainWindow->ProcessMouseMotion(XPos, YPos);
    }
}

void Aplication::AddTickObject(TickObject* Object) 
{
    TickObjects.push_back(Object);
}

void Aplication::Tick(float DeltaTime) 
{
    for (auto Object : TickObjects)
    {
        if (!Object)
        {
            continue;
        }
        Object->Tick(DeltaTime);
    }
}