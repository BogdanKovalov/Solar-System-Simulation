#include "PointLight.h"

PointLight::PointLight(float InDistance) : Light()
{
    SetCoeficients(InDistance);
}

void PointLight::SetCoeficients(float Distance) 
{
    LinearCoef = GetLinearCoef(Distance);
    QuadraticCoef = GetQuadraticCoef(Distance);
}

float PointLight::GetLinearCoef(float Distance)
{
    return 4.206f / (Distance - 0.9733f) + 0.00159f;
}

float PointLight::GetQuadraticCoef(float Distance)
{
    return 97.79f / (float)(pow(Distance, 2)) - 1.48f / Distance + 0.0097f;
}

PointLight::PointLight(float InDistance, FLightAspects const& InLightAspects) : Light(InLightAspects) 
{
    SetCoeficients(InDistance);
}

PointLight::PointLight(float InDistance, glm::vec3 InAmbient, glm::vec3 InDiffuse, glm::vec3 InSpecular)
    : Light(InAmbient, InDiffuse, InSpecular)
{
    SetCoeficients(InDistance);
}