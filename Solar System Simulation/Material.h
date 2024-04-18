#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>
#include "ModelUtilities.h"

#include <unordered_map>
#include <memory>

class Shader;

class Material
{
public:
    Material() = delete;
    Material(std::shared_ptr<Shader> Shader) : UsingShader(Shader){};

    void LoadTexturesToShader();

    bool IsTextureLoaded(ETextureType Type, std::string LocalPath);
    void AddTexture(ETextureType NewType, Texture NewTexture) { TypeTextureMap.emplace(NewType, NewTexture); }

    std::shared_ptr<Shader> GetShader() { return UsingShader; }

private:
    glm::vec3 AmbientColor;
    glm::vec3 DiffuseColor;
    glm::vec3 SpecularColor;
    float Shininess;

    std::unordered_map<ETextureType, Texture> TypeTextureMap;

    std::shared_ptr<Shader> UsingShader;

private:
    auto GetTextureByType(ETextureType Type) { return TypeTextureMap.find(Type); }
    size_t GetNumTexturesByType(ETextureType Type) { return TypeTextureMap.count(Type); }
};

class TexturedMaterial : public Material
{
public:
    std::unordered_map<ETextureType, Texture> TypeTextureMap;
};

#endif