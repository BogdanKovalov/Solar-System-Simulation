#pragma once
#ifndef _APLICATION_H_
#define _APLICATION_H_

#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Window;
class TickObject;
struct GLFWwindow;
struct GLFWmonitor;

class Aplication
{
public:
    Aplication();

    void CreateWindow(int Width, int Height, const char* Title, GLFWmonitor* Monitor, GLFWwindow* Share);

    virtual void Tick(float DeltaTime);

    static std::shared_ptr<Aplication> GetAPI();
    inline Window* GetWindow() const { return MainWindow.get(); }
    virtual inline glm::vec3 GetWorldUp() const { return WorldUp; }

    // if we need to change WorldUp vector in other API
    void SetWorldUp(glm::vec3 NewWorldUp) { WorldUp = NewWorldUp; }
    void AddTickObject(TickObject* Object);

    static void GLProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
    static void GLProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos);

protected:
    virtual void ProcessKeyboard(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
    virtual void ProcessMouseMotion(GLFWwindow* Window, double XPos, double YPos);

private:
    std::shared_ptr<Window> MainWindow;
    std::vector<TickObject*> TickObjects;

    glm::vec3 WorldUp;

    static std::shared_ptr<Aplication> API;
};

#endif