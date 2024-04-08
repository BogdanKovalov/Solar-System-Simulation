#pragma once
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Light.h"
#include <glm/glm.hpp>

class PointLight : public Light
{
public:
    PointLight() = delete;
    PointLight(float InDistance);
    PointLight(float InDistance, glm::vec3 InAmbient, glm::vec3 InDiffuse, glm::vec3 InSpecular);
    PointLight(float InDistance, FLightAspects const& InLightAspects);

    inline float GetLinearCoef() const { return LinearCoef; }
    inline float GetQuadraticCoef() const { return QuadraticCoef; }
    inline glm::vec3 GetLocation() const { return Location; }
    
    void SetLocation(glm::vec3 NewLocation) { Location = NewLocation; }

private:
    float LinearCoef;
    float QuadraticCoef;

    glm::vec3 Location = glm::vec3(0.0f);

private:
    void SetCoeficients(float Distance);
    float GetLinearCoef(float Distance);
    float GetQuadraticCoef(float Distance);
};

#endif
