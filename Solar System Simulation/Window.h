#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct GLFWwindow;
struct GLFWmonitor;
class Controller;

class Window
{
public:
    Window() = delete;
    Window(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share);

    void ProcessKeyboard(int Key, int Scancode, int Action, int Mods);
    void ProcessMouseMotion(int XPos, int YPos);

    inline int GetWidth() const { return Width; }
    inline int GetHeight() const { return Height; }
    inline GLFWwindow* GetGLWindow() { return GLWindow.get(); }
    glm::mat4 GetView() const;

private:
    std::shared_ptr<GLFWwindow> GLWindow;
    std::shared_ptr<Controller> WindowController;

    int Width;
    int Height;
};

#endif