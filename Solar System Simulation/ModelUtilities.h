#pragma once
#ifndef _MODEL_UTILITIES_H_
#define _MODEL_UTILITIES_H_

#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>

enum class ETextureType
{
    DIFFUSE,
    SPECULAR
};

namespace ModelUtilities
{
    std::string TypeToString(ETextureType Type);
    glm::vec3 GetGLMVec(aiVector3D AssimpVector);
} 

struct Vertex
{
    glm::vec3 Location;
    glm::vec3 Normal;
    glm::vec2 TextureCoords;
};

struct Texture
{
    unsigned int ID;
    ETextureType Type;
    std::string Path;
};

#endif  // !_MODEL_UTILITIES_H_
