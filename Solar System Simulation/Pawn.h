#pragma once
#ifndef _PAWN_H_
#define _PAWN_H_

#include <memory>
#include <glm/glm.hpp>

class Camera;
class InputHandler;

class Pawn
{
public:
    Pawn() = delete;
    Pawn(glm::vec3 Location = glm::vec3(0.0f), glm::vec3 Velocity = glm::vec3(0.0f));
    
    //Called by controller
    virtual void SetupInput(std::shared_ptr<InputHandler> InputComponent);

    glm::mat4 GetView() const;

private:
    std::shared_ptr<Camera> AttachedCamera;

    glm::vec3 Location;
    glm::vec3 Velocity;
};

#endif
