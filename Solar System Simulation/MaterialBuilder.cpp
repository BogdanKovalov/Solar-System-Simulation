#include "MaterialBuilder.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

std::shared_ptr<Material> MaterialBuilder::CreateMaterialFromAssimpMaterial(aiMaterial* AssimpMaterial, std::string Directory)
{
    std::shared_ptr<Material> CreatedMaterial(new Material(DefaultShader));
    ImportingDirectory = Directory;
    auto MaterialProperties = AssimpMaterial->mProperties;
    for (GLuint i = 0; i < AssimpMaterial->mNumProperties; ++i)
    {
        if (MaterialProperties[i]->mSemantic == aiTextureType_NONE)
        {
            continue;
        }
        aiTextureType Type = static_cast<aiTextureType>(MaterialProperties[i]->mSemantic);
        aiString LocalPath;
        AssimpMaterial->GetTexture(Type, 0, &LocalPath);
        if (CreatedMaterial->IsTextureLoaded(static_cast<ETextureType>(Type), LocalPath.C_Str()))
        {
            continue;
        }

        Texture NewTexture = CreateTexture(LocalPath.C_Str());
        CreatedMaterial->AddTexture(static_cast<ETextureType>(Type), NewTexture);
    }
    return CreatedMaterial;
}

Texture MaterialBuilder::CreateTexture(std::string LocalPath)
{
    Texture NewTexture;
    NewTexture.Path = LocalPath;
    glGenTextures(1, &NewTexture.ID);

    int Width, Height, NumComponents;
    unsigned char* data = stbi_load((ImportingDirectory + LocalPath).c_str(), &Width, &Height, &NumComponents, 0);
    if (!data)
    {
        std::cout << "Texture failed to load at path: " << (ImportingDirectory + LocalPath) << std::endl;
        stbi_image_free(data);
        return NewTexture;
    }

    GLenum Format = ModelUtilities::GetTextureFormatFromComponents(NumComponents);

    glBindTexture(GL_TEXTURE_2D, NewTexture.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return NewTexture;
}
