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
}
