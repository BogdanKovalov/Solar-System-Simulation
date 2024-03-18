#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

typedef unsigned int GLuint;
typedef char GLchar;

class Shader
{
public:
    GLuint Program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();
};

#endif