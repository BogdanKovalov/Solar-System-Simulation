#pragma once
#ifndef _MATERIAL_BUILDER_H_
#define _MATERIAL_BUILDER_H_

#include <memory>
#include <string>

class Material;
class Shader;
struct aiMaterial;
struct Texture;

class MaterialBuilder
{
public:
    MaterialBuilder() = delete;
    MaterialBuilder(std::shared_ptr<Shader> InDefaultShader) : DefaultShader(InDefaultShader){};
    std::shared_ptr<Material> CreateMaterialFromAssimpMaterial(aiMaterial* AssimpMaterial, std::string Directory);

private:
    std::string ImportingDirectory;
    std::shared_ptr<Shader> DefaultShader;

private:
    void SetMaterialColors(aiMaterial* AssimpMaterial, std::shared_ptr<Material> CreatingMaterial);
    Texture CreateTexture(std::string LocalPath);
};

#endif  // !_MATERIAL_BUILDER_H_
