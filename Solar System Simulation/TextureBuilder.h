#pragma once
#ifndef _TEXTURE_BUILDER_H_
#define _TEXTURE_BUILDER_H_

#include <vector>
#include <string>

#include "ModelUtilities.h"

struct aiMaterial;
struct Texture;
enum aiTextureType;

typedef unsigned int GLuint;

class TextureBuilder
{
public:
    std::vector<Texture>& CreateTextureFromMaterial(
        aiMaterial* Material, aiTextureType Type, ETextureType TextureType, std::string Directory);

private:
    std::vector<Texture> LoadedTextures;

private:
    GLuint ImportTexture(std::string Path);
};

#endif