#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Types.h"
#include "InputHandler.h"
#include "Controller.h"
#include "Window.h"
#include "Aplication.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <iostream>

GLuint GenerateTexture(const char* FileName, GLint TextureFormat)
{
    int Width = 0, Height = 0, NrChannels = 0;
    unsigned char* Data = stbi_load(FileName, &Width, &Height, &NrChannels, 0);

    if (!Data)
    {
        std::cout << "Failed to load image" << std::endl;
        stbi_image_free(Data);
        return 0;
    }

    GLuint Texture;
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, TextureFormat, Width, Height, 0, TextureFormat, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);

    return Texture;
}

int main()
{
    Aplication* API1 = new Aplication;
    // API1->CreateWindow(1000, 1000, "Solar System Simulation", nullptr, nullptr);
    auto MainWindow = API1->GetWindow();

    float Vertices[] = {
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.5f,
        -0.5f,
        -0.5f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        -1.0f,
        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        -1.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        -1.0f,

        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        -0.5f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,

        -0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.0f,
        -0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.0f,
        -0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.0f,

        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,

        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.5f,
        -0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.0f,
        -1.0f,
        0.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,

        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        -0.5f,
        0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,  // первый треугольник
        1, 2, 3   // второй треугольник
    };

    GLuint VBO;
    GLuint VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint LightVAO;
    glGenBuffers(1, &LightVAO);
    glBindVertexArray(LightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader MainShader("Shaders/Vertex.vert", "Shaders/Fragment.frag");
    Shader LightShader("Shaders/Vertex.vert", "Shaders/LightFragment.frag");

    GLuint BoxTexture = GenerateTexture("Box.png", GL_RGBA);
    GLuint SpecularMap = GenerateTexture("SpecularMap.png", GL_RGBA);
    GLuint EmissionMap = GenerateTexture("EmissionMap.jpg", GL_RGB);

    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f));

    int Width = MainWindow->GetWidth();
    int Height = MainWindow->GetHeight();
    glm::mat4 ProjectionMatrix(1.0f);
    ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);

    MainShader.SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));
    MainShader.SetMatrix4("ProjectionMatrix", glm::value_ptr(ProjectionMatrix));
    MainShader.SetMatrix3("NormalMatrix", glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(ModelMatrix)))));
    MainShader.SetInt("MeshMaterial.Diffuse", 0);
    MainShader.SetInt("MeshMaterial.Specular", 1);
    MainShader.SetInt("MeshMaterial.Emission", 2);
    MainShader.SetFloat("MeshMaterial.Shininess", 64);

    PointLight Light(50.0f);
    SpotLight SpotLight(glm::vec3(0.0f, 0.0f, -1.0f), 12.5f, 17.5f);
    SpotLight.SetLocation(glm::vec3(0.0f, 0.0f, 1.0f));

    MainShader.SetVec3("PointLight.Ambient", Light.GetAmbientAspect());
    MainShader.SetVec3("PointLight.Diffuse", Light.GetDiffuseAspect());
    MainShader.SetVec3("PointLight.Specular", Light.GetSpecularAspect());
    MainShader.SetFloat("PointLight.LinearCoef", Light.GetLinearCoef());
    MainShader.SetFloat("PointLight.QuadraticCoef", Light.GetQuadraticCoef());

    MainShader.SetVec3("SpotLight.Ambient", SpotLight.GetAmbientAspect());
    MainShader.SetVec3("SpotLight.Diffuse", SpotLight.GetDiffuseAspect());
    MainShader.SetVec3("SpotLight.Specular", SpotLight.GetSpecularAspect());
    MainShader.SetVec3("SpotLight.Location", SpotLight.GetLocation());
    MainShader.SetVec3("SpotLight.Direction", SpotLight.GetDirection());
    MainShader.SetFloat("SpotLight.CutOff", glm::cos(glm::radians(SpotLight.GetAngle())));
    MainShader.SetFloat("SpotLight.OuterCutOff", glm::cos(glm::radians(SpotLight.GetOuterAngle())));
    // MainShader.SetVec3("LightPos", glm::vec3(1.0f, 1.0f, 1.0f));

    LightShader.SetMatrix4("ProjectionMatrix", glm::value_ptr(ProjectionMatrix));

    glEnable(GL_DEPTH_TEST);

    double DeltaTime = 0.0;
    double LastTime = glfwGetTime();

    while (!glfwWindowShouldClose(MainWindow->GetGLWindow()))
    {
        DeltaTime = glfwGetTime() - LastTime;
        LastTime = glfwGetTime();

        glfwPollEvents();

        API1->Tick(DeltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, BoxTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, SpecularMap);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, EmissionMap);

        MainShader.SetMatrix4("ViewMatrix", glm::value_ptr(MainWindow->GetView()));
        MainShader.SetVec3("ViewPos", MainWindow->GetCameraLocation());
        LightShader.SetMatrix4("ViewMatrix", glm::value_ptr(MainWindow->GetView()));

        Light.SetLocation(glm::vec3(cos(25 * glm::radians(LastTime)), sin(25 * glm::radians(LastTime)), 1.0f));

        glm::mat4 LightModelMatrix(1.0f);
        LightModelMatrix = glm::translate(LightModelMatrix, Light.GetLocation());
        MainShader.SetVec3("PointLight.Location", Light.GetLocation());
        LightModelMatrix = glm::scale(LightModelMatrix, glm::vec3(0.25f));
        LightShader.SetMatrix4("ModelMatrix", glm::value_ptr(LightModelMatrix));

        MainShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        LightShader.Use();
        glBindVertexArray(LightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(MainWindow->GetGLWindow());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}