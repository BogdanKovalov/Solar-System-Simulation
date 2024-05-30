#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::failbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    Program = glCreateProgram();
    glAttachShader(Program, vertex);
    glAttachShader(Program, fragment);
    glLinkProgram(Program);

    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::SetMatrix4(const GLchar* Name, const GLfloat* Matrix) const
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(Program, Name), 1, GL_FALSE, Matrix);
}

void Shader::SetMatrix3(const GLchar* Name, const GLfloat* Matrix) const
{
    Use();
    glUniformMatrix3fv(glGetUniformLocation(Program, Name), 1, GL_FALSE, Matrix);
}

void Shader::SetVec3(const GLchar* Name, glm::vec3 Vec3) const
{
    Use();
    glUniform3f(glGetUniformLocation(Program, Name), Vec3.x, Vec3.y, Vec3.z);
}

void Shader::SetVec4(const GLchar* Name, glm::vec4 Vec) const
{
    Use();
    glUniform4f(glGetUniformLocation(Program, Name), Vec.x, Vec.y, Vec.z, Vec.w);
}

void Shader::SetInt(const GLchar* Name, const GLint Int) const
{
    Use();
    glUniform1i(glGetUniformLocation(Program, Name), Int);
}

void Shader::SetFloat(const GLchar* Name, const GLfloat Float) const
{
    Use();
    glUniform1f(glGetUniformLocation(Program, Name), Float);
}

void Shader::SetBool(const GLchar* Name, const bool Bool) const
{
    Use();
    glUniform1i(glGetUniformLocation(Program, Name), Bool);
}

void Shader::Use() const
{
    glUseProgram(Program);
}