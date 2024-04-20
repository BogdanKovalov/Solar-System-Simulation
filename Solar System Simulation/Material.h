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

    void SetAmbientColor(glm::vec4 NewAmbientColor) { AmbientColor = NewAmbientColor; }
    void SetDiffuseColor(glm::vec4 NewDiffuseColor) { DiffuseColor = NewDiffuseColor; }
    void SetSpecularColor(glm::vec4 NewSpecularColor) { SpecularColor = NewSpecularColor; }
    void SetShininess(float NewShininess) { Shininess = NewShininess; }

private:
    glm::vec4 AmbientColor;
    glm::vec4 DiffuseColor;
    glm::vec4 SpecularColor;
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