#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include <glm/gtc/matrix_transform.hpp>
#include <ECS/World.h>

typedef unsigned int GLuint;
typedef char GLchar;
typedef float GLfloat;
typedef int GLint;

class Shader : public Component
{
public:
    Shader(){};
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void SetMatrix4(const GLchar* Name, const GLfloat* Matrix);
    void SetMatrix3(const GLchar* Name, const GLfloat* Matrix);
    void SetVec3(const GLchar* Name, glm::vec3 Vec);
    void SetVec4(const GLchar* Name, glm::vec4 Vec);
    void SetInt(const GLchar* Name, const GLint Int);
    void SetFloat(const GLchar* Name, const GLfloat Float);
    void SetBool(const GLchar* Name, const bool Bool);

    void Use();

    void SetProgram(GLuint NewProgram) { Program = NewProgram; }

private:
    GLuint Program;
};

#endif