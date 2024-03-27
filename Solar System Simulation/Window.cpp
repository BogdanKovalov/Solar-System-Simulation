#include "Window.h"
#include "Controller.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share)
{
    auto DeleteFunction = [](GLFWwindow* GLWindow) { glfwDestroyWindow(GLWindow); };
    GLWindow = std::shared_ptr<GLFWwindow>(glfwCreateWindow(Width, Height, Title, Monitor, Share), DeleteFunction);
    if (!GLWindow.get())
    {
        return;
    }

    glfwMakeContextCurrent(GLWindow.get());
    this->Width = Width;
    this->Height = Height;

    WindowController = std::shared_ptr<Controller>(new Controller());
}

void Window::ProcessKeyboard(int Key, int Scancode, int Action, int Mods) 
{
    WindowController->ProcessKeyboard(Key, Scancode, Action, Mods);
}

void Window::ProcessMouseMotion(int XPos, int YPos) 
{
    WindowController->ProcessMouseMotion(XPos, YPos);
}

glm::mat4 Window::GetView() const
{
    return WindowController->GetView();
}