#pragma once
#ifndef _MODEL_UTILITIES_H_
#define _MODEL_UTILITIES_H_

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>

typedef unsigned int GLenum;

enum class ETextureType
{
    DIFFUSE = aiTextureType_DIFFUSE,
    SPECULAR = aiTextureType_SPECULAR,
    NORMAL = aiTextureType_HEIGHT,
};

struct Vertex
{
    glm::vec3 Location;
    glm::vec3 Normal;
    glm::vec2 TextureCoords;
};

struct Texture
{
    unsigned int ID;
    std::string Path;
};

namespace ModelUtilities
{
    std::string TypeToString(ETextureType Type);
    glm::vec3 GetGLMVec(aiVector3D AssimpVector);
    glm::vec4 GetGLMVecFromColor(aiColor4D Color);
    GLenum GetTextureFormatFromComponents(int NumComponents);

    const std::initializer_list<ETextureType> AllTextureTypes = {ETextureType::DIFFUSE, ETextureType::SPECULAR, ETextureType::NORMAL};
} 

#endif
