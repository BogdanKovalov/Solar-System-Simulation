#include "ShaderManager.h"
#include "Shader.h"

#include <string>
#include <iostream>
#include <filesystem>

ShaderManager::ShaderManager()
{
    std::string Path = "../Shaders";
    for (const auto& Entry : std::filesystem::directory_iterator(Path))
    {
        std::cout << Entry.path() << std::endl;
    }
}