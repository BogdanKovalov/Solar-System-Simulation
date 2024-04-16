#include "Material.h"

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
