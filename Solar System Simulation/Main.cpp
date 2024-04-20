#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Types.h"
#include "InputSystem/InputHandler.h"
#include "Controller.h"
#include "Window.h"
#include "Aplication.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Models/Model.h"
#include "ModelBuilder.h"

#include <iostream>

int main()
{
    Aplication* API1 = new Aplication;
    // API1->CreateWindow(1000, 1000, "Solar System Simulation", nullptr, nullptr);
    auto MainWindow = API1->GetWindow();

    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2.0f, 0.0f));
    // ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f));

    int Width = MainWindow->GetWidth();
    int Height = MainWindow->GetHeight();
    glm::mat4 ProjectionMatrix(1.0f);
    ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);

    PointLight Light(1000.0f, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
    SpotLight SpotLight(glm::vec3(0.0f, 0.0f, -1.0f), 12.5f, 17.5f);
    SpotLight.SetLocation(glm::vec3(0.0f, 0.0f, 1.0f));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    double DeltaTime = 0.0;
    double LastTime = glfwGetTime();

    std::shared_ptr<Shader> BackpackShader = std::shared_ptr<Shader>(new Shader("Shaders/Backpack.vert", "Shaders/Backpack.frag"));

    ModelBuilder Builder(BackpackShader);
    auto Boy = Builder.ImportModel("../Models/Earth/Earth.obj");

    BackpackShader->SetMatrix4("ProjectionMatrix", glm::value_ptr(ProjectionMatrix));

    BackpackShader->SetVec3("PointLight.Ambient", Light.GetAmbientAspect());
    BackpackShader->SetVec3("PointLight.Diffuse", Light.GetDiffuseAspect());
    BackpackShader->SetVec3("PointLight.Specular", Light.GetSpecularAspect());
    BackpackShader->SetFloat("PointLight.LinearCoef", Light.GetLinearCoef());
    BackpackShader->SetFloat("PointLight.QuadraticCoef", Light.GetQuadraticCoef());
    Light.SetLocation(glm::vec3(0.0f, 0.0f, 1.0f));
    BackpackShader->SetVec3("PointLight.Location", Light.GetLocation());
    BackpackShader->SetMatrix3("NormalMatrix", glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(ModelMatrix)))));

    while (!glfwWindowShouldClose(MainWindow->GetGLWindow()))
    {
        DeltaTime = glfwGetTime() - LastTime;
        LastTime = glfwGetTime();

        glfwPollEvents();

        API1->Tick((float)DeltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BackpackShader->SetMatrix4("ViewMatrix", glm::value_ptr(MainWindow->GetView()));
        BackpackShader->SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));
        BackpackShader->SetVec3("ViewPos", MainWindow->GetCameraLocation());
        Boy->Draw();

        glfwSwapBuffers(MainWindow->GetGLWindow());
    }

    glfwTerminate();
    return 0;
}