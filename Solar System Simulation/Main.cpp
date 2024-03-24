#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#include "Shader.h"

#include <iostream>

void ProcessInput(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

float MixCoef = 0.2f;

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

GLuint GenerateTexture(const char* FileName)
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);

    return Texture;
}

GLuint GenerateTextureWithAlpha(const char* FileName)
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);

    return Texture;
}

int main()
{
    auto Window = InitializeSystem();

    float Vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,    // верхняя правая
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // нижняя правая
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // нижняя левая
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f    // верхняя левая
    };

    unsigned int indices[] = {
        0, 1, 3,  // первый треугольник
        1, 2, 3   // второй треугольник
    };

    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader MainShader("Shaders/Vertex.v", "Shaders/Fragment.frag");

    GLuint ContainerTexture = GenerateTexture("Container.jpg");
    GLuint FaceTexture = GenerateTextureWithAlpha("Face.png");

    MainShader.Use();
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture1"), 0);
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture2"), 1);

    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();

        glClearColor(0.3f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ContainerTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, FaceTexture);
        glUniform1f(glGetUniformLocation(MainShader.Program, "MixCoef"), MixCoef);

        MainShader.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(Window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (glfwGetKey(Window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        MixCoef += 0.1f;  // измените это значение соответствующим образом (может быть слишком медленным или слишком быстрым, в
                            // зависимости от вашего системного оборудования)
        if (MixCoef >= 1.0f) MixCoef = 1.0f;
    }
    if (glfwGetKey(Window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        MixCoef -= 0.1f;  // измените это значение соответствующим образом (может быть слишком медленным или слишком быстрым, в
                            // зависимости от вашего системного оборудования)
        if (MixCoef <= 0.0f) MixCoef = 0.0f;
    }
}