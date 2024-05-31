#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Types.h"
#include "InputSystem/InputHandler.h"
#include "Controller.h"
#include "Window.h"
#include "Game.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Models/Model.h"
#include "Models/ModelBuilder.h"
#include "Models/RenderSystem.h"
#include "Models/ModelComponents.h"
#include "ShaderManager.h"

#include <iostream>
#include <unordered_set>

int main()
{
    Game* SolarSystemSimulation = new Game;
    auto MainWindow = SolarSystemSimulation->GetWindow();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    double DeltaTime = 0.0;
    double LastTime = glfwGetTime();

    ModelBuilder Builder{};

    std::shared_ptr<World> MyWorld = SolarSystemSimulation->GetWorld();

    EntityID ID = MyWorld->CreateEntity();
    MyWorld->AddComponent<ModelComponent>(ID);
    ModelComponent* Comp = MyWorld->GetComponent<ModelComponent>(ID);
    auto TempComp = Builder.ImportModel("../Models/Earth/Earth.obj").get();
    Comp->Meshes = TempComp->Meshes;
    Comp->PosComponent->Location = glm::vec3(-1.0f);

    ID = MyWorld->CreateEntity();
    MyWorld->AddComponent<ModelComponent>(ID);
    Comp = MyWorld->GetComponent<ModelComponent>(ID);
    Comp->Meshes = TempComp->Meshes;

    ID = MyWorld->CreateEntity();
    MyWorld->AddComponent<PointLight>(ID);
    PointLight* Light = MyWorld->GetComponent<PointLight>(ID);
    Light->SetLocation(glm::vec3(2.0f, 0.0f, 0.0f));

    while (!glfwWindowShouldClose(MainWindow->GetGLWindow()))
    {
        DeltaTime = glfwGetTime() - LastTime;
        LastTime = glfwGetTime();

        glfwPollEvents();

         SolarSystemSimulation->Tick((float)DeltaTime);

        glfwSwapBuffers(MainWindow->GetGLWindow());
    }

    glfwTerminate();
    return 0;
}
