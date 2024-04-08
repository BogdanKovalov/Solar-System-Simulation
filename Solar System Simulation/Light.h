#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/glm.hpp>

struct FLightAspects
{
    glm::vec3 Ambient = glm::vec3(1.0f);
    glm::vec3 Diffuse = glm::vec3(1.0f);
    glm::vec3 Specular = glm::vec3(1.0f);
};

class Light
{
public:
    Light(){};
    Light(glm::vec3 InAmbient, glm::vec3 InDiffuse, glm::vec3 InSpecular)
    {
        LightAspects.Ambient = InAmbient;
        LightAspects.Diffuse = InDiffuse;
        LightAspects.Specular = InSpecular;
    };

    Light(FLightAspects const& InLightAspects) : LightAspects(InLightAspects){};

    inline glm::vec3 GetAmbientAspect() const { return LightAspects.Ambient; }
    inline glm::vec3 GetDiffuseAspect() const { return LightAspects.Diffuse; }
    inline glm::vec3 GetSpecularAspect() const { return LightAspects.Specular; }

protected:
    FLightAspects LightAspects;
};

#endif
