#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include <glm/gtc/matrix_transform.hpp>
#include <ECS/World.h>

typedef unsigned int GLuint;
typedef char GLchar;
typedef float GLfloat;
typedef int GLint;

enum EShaderType
{
    BASIC,
    NORMALMAP
};

class Shader : public Component
{
public:
    Shader(){};
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void SetMatrix4(const GLchar* Name, const GLfloat* Matrix) const;
    void SetMatrix3(const GLchar* Name, const GLfloat* Matrix) const;
    void SetVec3(const GLchar* Name, glm::vec3 Vec) const;
    void SetVec4(const GLchar* Name, glm::vec4 Vec) const;
    void SetInt(const GLchar* Name, const GLint Int) const;
    void SetFloat(const GLchar* Name, const GLfloat Float) const;
    void SetBool(const GLchar* Name, const bool Bool) const;

    inline void SetProgram(GLuint NewProgram) { Program = NewProgram; }
    inline void SetShaderType(EShaderType NewType) { Type = NewType; }

    inline EShaderType GetType() const { return Type; }

    void Use() const;

private:
    EShaderType Type;
    GLuint Program;
};

#endif