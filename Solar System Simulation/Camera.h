#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

#include "TickObject.h"

class Camera : TickObject
{
public:
    Camera() = delete;
    Camera(glm::vec3 Location, glm::vec3 TargetView);

    void Tick(float DeltaTime) override;

    glm::mat4 GetViewMatrix() const;
    inline glm::vec3 GetForwardVector() const { return -ForwardVector; }
    inline glm::vec3 GetRightVector() const { return RightVector; }
    inline glm::vec3 GetUpVector() const { return UpVector; }

    inline void AddOffset(glm::vec3 Offset) { Location += Offset; }
    inline void AddVelocity(glm::vec3 AddVelocity) { Velocity += AddVelocity; }

private:
    glm::vec3 Location;
    glm::vec3 Velocity;
    glm::vec3 ForwardVector;
    glm::vec3 RightVector;
    glm::vec3 UpVector;
};

#endif _CAMERA_H_