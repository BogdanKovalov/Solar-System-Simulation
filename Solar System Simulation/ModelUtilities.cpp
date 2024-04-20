#include "ModelUtilities.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string ModelUtilities::TypeToString(ETextureType Type)
{
    switch (Type)
    {
        case ETextureType::DIFFUSE: return "TextureDiffuse";
        case ETextureType::SPECULAR: return "TextureSpecular";
        case ETextureType::NORMAL: return "TextureNormal";
        default: break;
    }
    return std::string();
}

glm::vec3 ModelUtilities::GetGLMVec(aiVector3D AssimpVector)
{
    return glm::vec3(AssimpVector.x, AssimpVector.y, AssimpVector.z);
}

glm::vec4 ModelUtilities::GetGLMVecFromColor(aiColor4D Color)
{
    return glm::vec4(Color.r, Color.g, Color.b, Color.a);
}

GLenum ModelUtilities::GetTextureFormatFromComponents(int NumComponents)
{
    switch (NumComponents)
    {
        case 1: return GL_RED;
        case 3: return GL_RGB;
        case 4: return GL_RGBA;
        default: return GLenum();
    }
}