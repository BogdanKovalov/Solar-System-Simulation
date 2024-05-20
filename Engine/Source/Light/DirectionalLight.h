#pragma once
#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : Light
{
public:
    DirectionalLight(){};
    DirectionalLight(glm::vec3 InDirection) : Direction(InDirection){};
    DirectionalLight(glm::vec3 InAmbient, glm::vec3 InDiffuse, glm::vec3 InSpecular, glm::vec3 InDirection)
        : Light(InAmbient, InDiffuse, InSpecular), Direction(InDirection){};

    DirectionalLight(FLightAspects InLightAspects, glm::vec3 InDirection) : Light(InLightAspects), Direction(InDirection) {}

    inline glm::vec3 GetDirection() const { return Direction; }

private:
    glm::vec3 Direction = glm::vec3(0.0f);
};

#endif
