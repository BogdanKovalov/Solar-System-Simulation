#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class Camera
{
public:
    Camera() = delete;
    Camera(glm::vec3 Location, glm::vec3 TargetView, glm::vec3 WorldUp);

    glm::mat4 GetViewMatrix() const;
    inline glm::vec3 GetForwardVector() const { return -ForwardVector; }
    inline glm::vec3 GetRightVector() const { return RightVector; }
    inline glm::vec3 GetUpVector() const { return UpVector; }

    inline void AddOffset(glm::vec3 Offset) { Location += Offset; }

private:
    glm::vec3 Location;
    glm::vec3 ForwardVector;
    glm::vec3 RightVector;
    glm::vec3 UpVector;
};

#endif _CAMERA_H_