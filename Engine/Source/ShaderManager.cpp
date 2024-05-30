#include "ShaderManager.h"
#include "Shader.h"
#include "Game.h"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

ShaderManager::ShaderManager(FObjectInitializer const& Initializer) : Entity(Initializer)
{
    for (const auto& Entry : std::filesystem::recursive_directory_iterator(ShaderUtilities::ShaderPath))
    {
        std::string FileName = ShaderUtilities::GetFileName(Entry.path());
        auto FoundShaderProgram = NameProgramMap.find(FileName);
        if (FoundShaderProgram != NameProgramMap.end())
        {
            continue;
        }

        FShaderPathType ShaderPathType;
        ShaderPathType.FilePath = Entry.path();
        ShaderPathType.Type = ShaderUtilities::GetShaderFileType(FileName);

        std::vector<FShaderPathType> MatchingShaderFiles = FindMatchingShaderFiles(ShaderPathType);
        MatchingShaderFiles.push_back(ShaderPathType);

        std::vector<GLuint> CompiledShaders;
        for (auto Shader : MatchingShaderFiles)
        {
            CompiledShaders.push_back(CompileShader(Shader));
        }
        GLuint ProgramID = LinkShaders(CompiledShaders);
        NameProgramMap.emplace(FileName, ProgramID);
        Component* CreatedComp = OwningWorld->AddComponent<Shader>(ID);
        if (Shader* ShaderComp = dynamic_cast<Shader*>(CreatedComp))
        {
            ShaderComp->SetProgram(ProgramID);
            ShaderComp->SetShaderType(ShaderUtilities::GetShaderType(FileName));
        }
    }
}

EShaderFileType ShaderUtilities::GetShaderFileType(std::string const& ShaderFile)
{
    std::string FileExtension = ShaderFile.substr(ShaderFile.find_last_of('.') + 1);
    if (FileExtension == VertexShaderExtension)
    {
        return EShaderFileType::VERTEX;
    }
    if (FileExtension == FragmentShaderExtension)
    {
        return EShaderFileType::FRAGMENT;
    }
    return EShaderFileType();
}

std::vector<FShaderPathType> ShaderManager::FindMatchingShaderFiles(FShaderPathType const& ShaderPathType)
{
    std::string FileName = ShaderUtilities::GetFileName(ShaderPathType.FilePath);
    std::vector<FShaderPathType> MatchingShaders;
    for (const auto& Entry : std::filesystem::recursive_directory_iterator(ShaderUtilities::ShaderPath))
    {
        std::string FoundName = ShaderUtilities::GetFileName(Entry.path());
        EShaderFileType ShaderType = ShaderUtilities::GetShaderFileType(Entry.path().string());
        if (FoundName == FileName && ShaderType != ShaderPathType.Type)
        {
            MatchingShaders.push_back(FShaderPathType(ShaderType, Entry.path()));
        }
    }
    return MatchingShaders;
}

GLuint ShaderManager::CompileShader(FShaderPathType const& ShaderPathType) const
{
    std::stringstream ShaderCode;
    std::ifstream ShaderFile(ShaderPathType.FilePath);
    if (!ShaderFile)
    { 
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::" << ShaderPathType.FilePath << "\n";
    }
    ShaderCode << ShaderFile.rdbuf();
    ShaderFile.close();

    GLuint ShaderID = glCreateShader(ShaderUtilities::ConvertToGLType(ShaderPathType.Type));
    std::string StringCode = ShaderCode.str();
    GLchar const* GLShaderCode = StringCode.c_str();
    glShaderSource(ShaderID, 1, &GLShaderCode, NULL);
    glCompileShader(ShaderID);

    GLint Success;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        GLchar InfoLog[512];
        glGetShaderInfoLog(ShaderID, 512, NULL, InfoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED" << InfoLog << "\n";
    }
    return ShaderID;
}

GLuint ShaderManager::LinkShaders(std::vector<GLuint> ShadersToLink)
{
    GLuint ProgramID = glCreateProgram();
    for (auto Shader : ShadersToLink)
    {
        glAttachShader(ProgramID, Shader);
    }
    glLinkProgram(ProgramID);

    GLint Success;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        GLchar InfoLog[512];
        glGetProgramInfoLog(ProgramID, 512, NULL, InfoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINK FAILED" << InfoLog << "\n";
    }
    for (auto Shader : ShadersToLink)
    {
        glDeleteShader(Shader);
    }

    return ProgramID;
}

unsigned int ShaderUtilities::ConvertToGLType(EShaderFileType Type)
{
    switch (Type)
    {
        case EShaderFileType::NONE: break;
        case EShaderFileType::VERTEX: return GL_VERTEX_SHADER;
        case EShaderFileType::FRAGMENT: return GL_FRAGMENT_SHADER;
        default: break;
    }
    return GLenum();
}

std::string ShaderUtilities::GetFileName(std::filesystem::path const& FilePath)
{
    std::string FileName = FilePath.filename().string();
    size_t DotPos = FileName.find_first_of('.');
    if (DotPos == std::string::npos)
    {
        return std::string();
    }
    FileName.erase(DotPos);
    return FileName;
}

EShaderType ShaderUtilities::GetShaderType(std::string const& FileName)
{
    if (FileName == "Basic")
    {
        return EShaderType::BASIC;
    }
    if (FileName == "NormalMap")
    {
        return EShaderType::NORMALMAP;
    }
    return EShaderType();
}