#pragma once
#ifndef _MODEL_COMPONENT_H_
#define _MODEL_COMPONENT_H_

#include "ECS/World.h"
#include "Models/ModelUtilities.h"
#include "Models/Material.h"
#include "Game.h"

#include <glm/glm.hpp>

typedef unsigned int GLuint;

struct PositionComponent : public Component
{
    glm::vec3 Location = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);
};

struct MeshComponent: public Component
{
public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<Vertex> Vertices;
    std::shared_ptr<Material> MeshMaterial;
    std::vector<GLuint> Indices;
};

struct ModelComponent : public Component
{
    std::shared_ptr<PositionComponent> PosComponent = std::make_shared<PositionComponent>();
    std::vector<std::shared_ptr<MeshComponent>> Meshes;
};

struct CameraComponent : public Component
{
    CameraComponent() 
    {
        glm::vec3 TargetView(0.0f, 0.0f, -1.0f);
        auto API = Game::GetAPI();
        if (API)
        {
            glm::vec3 WorldUp = Game::GetAPI()->GetWorldUp();
            ForwardVector = glm::normalize(PosComponent->Location - TargetView);
            RightVector = glm::normalize(glm::cross(ForwardVector, WorldUp));
            UpVector = glm::cross(RightVector, ForwardVector);
        }
    }

    std::shared_ptr<PositionComponent> PosComponent = std::make_shared<PositionComponent>();
    glm::vec3 ForwardVector;
    glm::vec3 RightVector;
    glm::vec3 UpVector;
};

#endif  // !_MODEL_COMPONENT_H_
