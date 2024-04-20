#include "Material.h"
#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef unsigned int GLuint;

void Material::LoadTexturesToShader() 
{
    if (!UsingShader)
    {
        return;
    }

    UsingShader->SetVec4("MeshMaterial.Ambient", AmbientColor);
    UsingShader->SetVec4("MeshMaterial.Diffuse", DiffuseColor);
    UsingShader->SetVec4("MeshMaterial.Specular", SpecularColor);
    UsingShader->SetFloat("MeshMaterial.Shininess", Shininess);

    GLuint NumLoadedTextures = 0;

    for (auto TextureType : ModelUtilities::AllTextureTypes)
    {
        auto Textures = GetTextureByType(TextureType);
        for (int i = 0; i < GetNumTexturesByType(TextureType); ++i)
        {
            if (TextureType == ETextureType::NORMAL)
            {
                UsingShader->SetBool("MeshMaterial.HasNormalMap", true);
            }
            glActiveTexture(GL_TEXTURE0 + NumLoadedTextures);
            std::string TextureName = ModelUtilities::TypeToString(TextureType);
            UsingShader->SetInt(("MeshMaterial." + TextureName + std::to_string(i)).c_str(), NumLoadedTextures++);
            glBindTexture(GL_TEXTURE_2D, Textures->second.ID);
            ++Textures;
        }
    }
}

bool Material::IsTextureLoaded(ETextureType Type, std::string LocalPath)
{
    auto Found = TypeTextureMap.find(Type);
    if (Found == TypeTextureMap.end())
    {
        return false;
    }
    if (Found->second.Path == LocalPath)
    {
        return true;
    }
    return false;
}
