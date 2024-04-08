#pragma once
#ifndef _SPOT_LIGHT_H_
#define _SPOT_LIGHT_H_

#include "Light.h"

#include <glm/glm.hpp>

class SpotLight : public Light
{
public:
    SpotLight() = delete;
    SpotLight(glm::vec3 InDirection, float InAngle, float InOuterAngle) : Direction(InDirection), Angle(InAngle), OuterAngle(InOuterAngle){};
    SpotLight(glm::vec3 InDirection, float InAngle, float InOuterAngle, glm::vec3 InAmbient, glm::vec3 InDiffuse, glm::vec3 InSpecular)
        : Light(InAmbient, InDiffuse, InSpecular), Direction(InDirection), Angle(InAngle), OuterAngle(InOuterAngle){};
    SpotLight(glm::vec3 InDirection, float InAngle, float InOuterAngle, FLightAspects const& InLightAspects)
        : Light(InLightAspects), Direction(InDirection), Angle(InAngle), OuterAngle(InOuterAngle){};

    inline glm::vec3 GetLocation() const { return Location; }
    inline glm::vec3 GetDirection() const { return Direction; }
    inline float GetAngle() const { return Angle; }
    inline float GetOuterAngle() const { return OuterAngle; }

    inline void SetLocation(glm::vec3 NewLocation) { Location = NewLocation; }
    inline void SetDirection(glm::vec3 NewDirection) { Direction = NewDirection; }
    inline void SetAngle(float NewAngle) { Angle = NewAngle; }
    inline void SetOuterAngle(float NewOuterAngle) { OuterAngle = NewOuterAngle; }

private:
    glm::vec3 Location = glm::vec3(0.0f);
    glm::vec3 Direction = glm::vec3(0.0f);
    float Angle = 0.0f;
    float OuterAngle = 0.0f;
};

#endif
