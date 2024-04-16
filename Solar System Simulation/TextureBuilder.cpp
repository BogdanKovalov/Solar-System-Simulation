#include "TextureBuilder.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Image/stb_image.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

std::vector<Texture> TextureBuilder::CreateTextureFromMaterial(
    aiMaterial* Material, aiTextureType Type, ETextureType TextureType, std::string Directory)
{
    std::vector<Texture> Textures;
    for (GLuint i = 0; i < Material->GetTextureCount(Type); ++i)
    {
        aiString LocalPath;
        Material->GetTexture(Type, i, &LocalPath);
        bool Skip = false;
        for (GLuint i = 0; i < LoadedTextures.size(); ++i)
        {
            if (std::strcmp(LoadedTextures[i].Path.data(), LocalPath.C_Str()) == 0)
            {
                Textures.push_back(LoadedTextures[i]);
                Skip = true;
                break;
            }
        }

        if (!Skip)
        {
            Texture NewTexture;
            NewTexture.ID = ImportTexture(Directory + LocalPath.C_Str());
            NewTexture.Path = LocalPath.C_Str();
            Textures.push_back(NewTexture);
            LoadedTextures.push_back(NewTexture);
        }
    }
    return Textures;
}

GLuint TextureBuilder::ImportTexture(std::string Path)
{
    GLuint TextureID;
    glGenTextures(1, &TextureID);

    int Width, Height, NumComponents;
    unsigned char* data = stbi_load(Path.c_str(), &Width, &Height, &NumComponents, 0);
    if (!data)
    {
        std::cout << "Texture failed to load at path: " << Path << std::endl;
        stbi_image_free(data);
        return TextureID;
    }

    GLenum Format = 0;
    if (NumComponents == 1)
    {
        Format = GL_RED;
    }
    else if (NumComponents == 3)
    {
        Format = GL_RGB;
    }
    else if (NumComponents == 4)
    {
        Format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return TextureID;
}