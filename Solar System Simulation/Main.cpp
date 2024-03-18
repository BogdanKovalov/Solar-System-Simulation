#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#include "Shader.h"

#include <iostream>

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);

    return Texture;
}

void Try() 
{
    auto Window = InitializeSystem();
    Shader MainShader("Shaders/Vertex.v", "Shaders/Fragment.frag");
    float vertices[] = {
        // ����������        // �����            // ���������� ����������
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,    // ������� ������ �������
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // ������ ������ �������
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // ������ ����� �������
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f    // ������� ����� �������
    };
    unsigned int indices[] = {
        0, 1, 3,  // ������ �����������
        1, 2, 3   // ������ �����������
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ������������ ��������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �������� ���������� ���������
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // �������� � �������� ��������
    unsigned int texture1, texture2;
    // �������� �1 - ���������� ����
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // ��������� ���������� ��������� ��������
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // ��������� ������ ��������� �������� GL_REPEAT (����������� ����� ���������)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // ��������� ���������� ���������� ��������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // �������� �����������, �������� �������� � ������������� ������-�������
    int width, height, nrChannels;

    unsigned char* data = stbi_load("Container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // �������� �2 - �������
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // ��������� ���������� ��������� ��������
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // ��������� ������ ��������� �������� GL_REPEAT (����������� ����� ���������)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // ��������� ���������� ���������� ��������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // �������� �����������, �������� �������� � ������������� ������-�������
    data = stbi_load("Face.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // ���� awesomeface.png ����� �����-����� (������������), ������� ���������� ������������ �������� GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // ��������� OpenGL ����� ������� � ������ ����������� ����� ����������� (��� ����� ������� ��������)
    MainShader.Use();  // �� �������� ������������ ������ ����� ���������� uniform-����������!

    // ������������� ��������
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture1"), 0);
    // ���� � ������� ���������� ������
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture2"), 1);

    // ���� ����������
    while (!glfwWindowShouldClose(Window))
    {

        // ���������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // �������� ������� � ��������������� ���������� ������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // ��������� �����
        MainShader.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: ����� ���������� front- � back- �������. ������������ ������� �����/������ (���� �� ������/�������� ������, ���������
        // ������ ���� � �.�.)
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    // �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

int main()
{
    Try();
    return 0;
    auto Window = InitializeSystem();

    float Vertices[] = {
        // ����������        // �����            // ���������� ����������
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,    // ������� ������
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // ������ ������
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // ������ �����
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f    // ������� �����
    };

     unsigned int indices[] = {
        0, 1, 3,  // ������ �����������
        1, 2, 3   // ������ �����������
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
    GLuint FaceTexture = GenerateTexture("Face.png");

    MainShader.Use();
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture1"), 0);
    glUniform1i(glGetUniformLocation(MainShader.Program, "Texture2"), 1);

    while (!glfwWindowShouldClose(Window))
    {
        glClearColor(0.3f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        MainShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ContainerTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, FaceTexture);
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