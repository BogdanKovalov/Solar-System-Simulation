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

#include <iostream>

void ProcessInput(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

InputHandler Input;

GLFWwindow* InitializeSystem()
{
    int Success = glfwInit();
    if (Success == GLFW_FALSE)
    {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    auto Window = glfwCreateWindow(1000, 1000, "Solar System Simulation", nullptr, nullptr);
    if (!Window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(Window);
    Success = glewInit();

    int Width = 0, Height = 0;
    glfwGetFramebufferSize(Window, &Width, &Height);
    glViewport(0, 0, Width, Height);

    glfwSetKeyCallback(Window, ProcessInput);

    return Window;
}

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
    auto Window = InitializeSystem();

    float Vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f,
        1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f,
        0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f,
        0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    unsigned int indices[] = {
        0, 1, 3,  // ������ �����������
        1, 2, 3   // ������ �����������
    };

    GLuint VBO;
    GLuint VAO;
    // GLuint EBO;
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader MainShader("Shaders/Vertex.v", "Shaders/Fragment.frag");

    GLuint ContainerTexture = GenerateTexture("Container.jpg", GL_RGB);
    GLuint FaceTexture = GenerateTexture("Face.png", GL_RGBA);

    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f));

    int Width, Height;
    glfwGetFramebufferSize(Window, &Width, &Height);
    glm::mat4 ProjectionMatrix(1.0f);
    ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);

    Camera MainCamera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    MainShader.SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));
    MainShader.SetMatrix4("ProjectionMatrix", glm::value_ptr(ProjectionMatrix));
    MainShader.SetInt("Texture1", 0);
    MainShader.SetInt("Texture2", 1);

    glEnable(GL_DEPTH_TEST);

    Input.Bind(EKey::W, ETriggerEvent::PRESSED, std::bind(&Camera::AddOffset, &MainCamera, MainCamera.GetForwardVector() * 5.0f));

    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();

        glClearColor(0.3f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ContainerTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, FaceTexture);

            MainShader.SetMatrix4("ViewMatrix", glm::value_ptr(MainCamera.GetViewMatrix()));

        MainShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(Window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods) 
{
    if (Key == GLFW_KEY_W && glfwGetKey(Window, Key) == GLFW_PRESS)
    {
        Input.InputTriggered(EKey::W, ETriggerEvent::PRESSED);
    }
}