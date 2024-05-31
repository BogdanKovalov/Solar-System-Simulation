#pragma once
#ifndef _PAWN_H_
#define _PAWN_H_

#include "ECS/Entity.h"
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

    inline void AddVelocity(glm::vec3 VelocityToAdd) { Velocity += VelocityToAdd; }
    inline void SetVelocity(glm::vec3 NewVelocity) { Velocity = NewVelocity; }
    inline void AddOffset(glm::vec3 Offset);
    void Rotate(glm::vec2 YawAndPitch);

    glm::vec3 GetForwardVector() const;
    glm::vec3 GetRightVector() const;
    glm::vec3 GetUpVector() const;

private:
    void Tick(float DeltaTime);

    std::shared_ptr<TickComponent> PawnTickComponent;
    std::shared_ptr<PositionComponent> PosComponent;
    std::shared_ptr<CameraComponent> PawnCameraComponent;

    glm::vec3 Velocity = glm::vec3(0.0f);
};

#endif
