#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <glm/glm.hpp>
#include "ModelUtilities.h"
#include "Shader.h"

#include <unordered_map>
#include <memory>

class Shader;

class Material
{
public:
    Material(){};
    //Material(std::shared_ptr<Shader> Shader) : UsingShader(Shader){};

    void LoadPropertiesToShader(Shader const* LoadShader) const;

    bool IsTextureLoaded(ETextureType Type, std::string LocalPath);
    void AddTexture(ETextureType NewType, Texture NewTexture) { TypeTextureMap.emplace(NewType, NewTexture); }

    EShaderType GetShaderType() const { return ShaderType; }

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

    EShaderType ShaderType = EShaderType::BASIC; 

private:
    auto GetTextureByType(ETextureType Type) const { return TypeTextureMap.find(Type); }
    size_t GetNumTexturesByType(ETextureType Type) const { return TypeTextureMap.count(Type); }
};

class TexturedMaterial : public Material
{
public:
    std::unordered_map<ETextureType, Texture> TypeTextureMap;
};

#endif