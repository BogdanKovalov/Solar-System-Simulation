#pragma once
#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include "ECS/Entity.h"

class Shader;
struct FObjectInitializer;
enum EShaderType;
typedef unsigned int GLuint;
typedef unsigned int GLenum;

enum class EShaderFileType
{
    NONE,
    VERTEX,
    FRAGMENT
};

struct FShaderPathType
{
    FShaderPathType() : Type(EShaderFileType::NONE), FilePath(std::filesystem::path()){};
    FShaderPathType(EShaderFileType InType, std::filesystem::path InFilePath) : Type(InType), FilePath(InFilePath){};
    EShaderFileType Type;
    std::filesystem::path FilePath;
};

namespace ShaderUtilities
{

EShaderFileType GetShaderFileType(std::string const& ShaderFile);
EShaderType GetShaderType(std::string const& FileName);
unsigned int ConvertToGLType(EShaderFileType Type);
std::string GetFileName(std::filesystem::path const& FilePath);

std::string const ShaderPath = "../Shaders";
std::string const VertexShaderExtension = "vert";
std::string const FragmentShaderExtension = "frag";

}  // namespace ShaderUtilities

class ShaderManager : public Entity
{
public:
    ShaderManager() = delete;
    ShaderManager(FObjectInitializer const& Initializer);

private:
    std::vector<Shader*> ShaderPrograms;
    std::unordered_map<std::string, GLuint> NameProgramMap;

private:
    std::vector<FShaderPathType> FindMatchingShaderFiles(FShaderPathType const& ShaderPathType);
    GLuint CompileShader(FShaderPathType const& ShaderPathType) const;
    GLuint LinkShaders(std::vector<GLuint> ShadersToLink);
};

#endif  // !_SHADER_MANAGER_H_