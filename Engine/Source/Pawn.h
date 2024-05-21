#pragma once
#ifndef _PAWN_H_
#define _PAWN_H_

#include "Models/ModelComponents.h"

#include <memory>
#include <glm/glm.hpp>

class Camera;
class InputHandler;
struct TickComponent;
struct FObjectInitializer;

class Pawn : public Entity
{
public:
    Pawn() = delete;
    Pawn(FObjectInitializer const& Initializer);

    void Tick(float DeltaTime);

    inline void AddVelocity(glm::vec3 VelocityToAdd) { Velocity += VelocityToAdd; }
    inline void SetVelocity(glm::vec3 NewVelocity) { Velocity = NewVelocity; }
    inline void AddOffset(glm::vec3 Offset);
    void Rotate(glm::vec2 YawAndPitch);

    glm::vec3 GetForwardVector() const;
    glm::vec3 GetRightVector() const;
    glm::vec3 GetUpVector() const;
    glm::mat4 GetView() const;
    glm::vec3 GetCameraLocation() const;

private:
    std::shared_ptr<Camera> AttachedCamera;

    std::shared_ptr<TickComponent> PawnTickComponent;
    std::shared_ptr<PositionComponent> PosComponent;

    glm::vec3 Location = glm::vec3(0.0f);
    glm::vec3 Velocity = glm::vec3(0.0f);
};

#endif
