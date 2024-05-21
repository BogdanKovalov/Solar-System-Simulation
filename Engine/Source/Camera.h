#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
public:
    Camera() = delete;
    Camera(glm::vec3 Location, glm::vec3 TargetView);

    //void Tick(float DeltaTime) override;

    glm::mat4 GetViewMatrix() const;
    inline glm::vec3 GetForwardVector() const { return -ForwardVector; }
    inline glm::vec3 GetRightVector() const { return RightVector; }
    inline glm::vec3 GetUpVector() const { return UpVector; }
    glm::vec3 GetLocation() const;

    inline void AddOffset(glm::vec3 Offset) { Location += Offset; }
    inline void AddVelocity(glm::vec3 AddVelocity) { Velocity += AddVelocity; }
    void Rotate(glm::vec2 YawAndPitch);

private:
    glm::vec3 Location;
    glm::vec3 Velocity;
    glm::vec3 ForwardVector;
    glm::vec3 RightVector;
    glm::vec3 UpVector;

    glm::vec3 Rotation = glm::vec3(0.0f);
};

#endif _CAMERA_H_