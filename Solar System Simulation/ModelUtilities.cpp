#include "ModelUtilities.h"

std::string ModelUtilities::TypeToString(ETextureType Type)
{
    switch (Type)
    {
        case ETextureType::DIFFUSE: return "TextureDiffuse";
        case ETextureType::SPECULAR: return "TextureSpecular";
        default: break;
    }
    return std::string();
}

glm::vec3 ModelUtilities::GetGLMVec(aiVector3D AssimpVector)
{
    return glm::vec3(AssimpVector.x, AssimpVector.y, AssimpVector.z);
}
