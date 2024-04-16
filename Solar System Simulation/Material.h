#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>
#include "ModelUtilities.h"

#include <unordered_map>

class Shader;

class Material
{
public:
    auto GetTextureByType(ETextureType Type) { return TypeTextureMap.find(Type); }
    bool IsTextureLoaded(ETextureType Type, std::string LocalPath);
    size_t GetNumTexturesByType(ETextureType Type) { return TypeTextureMap.count(Type); }
    void AddTexture(ETextureType NewType, Texture NewTexture) { TypeTextureMap.emplace(NewType, NewTexture); }
    Shader* GetShader() { return UsingShader; }

private:
    glm::vec3 AmbientColor;
    glm::vec3 DiffuseColor;
    glm::vec3 SpecularColor;
    float Shininess;

    std::unordered_map<ETextureType, Texture> TypeTextureMap;

    Shader* UsingShader;
};

class TexturedMaterial : public Material
{
public:
    std::unordered_map<ETextureType, Texture> TypeTextureMap;
};

#endif