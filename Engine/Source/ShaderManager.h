#pragma once
#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <vector>

class Shader;

class ShaderManager
{
public:
    ShaderManager();

private:
    std::vector<Shader*> Shaders;
};

#endif  // !_SHADER_MANAGER_H_