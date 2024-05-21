#pragma once
#ifndef _MODEL_COMPONENT_H_
#define _MODEL_COMPONENT_H_

#include "ECS/World.h"
#include "Models/ModelUtilities.h"
#include "Models/Material.h"

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
    std::shared_ptr<PositionComponent> PosComponent = std::shared_ptr<PositionComponent>(new PositionComponent);
    std::vector<std::shared_ptr<MeshComponent>> Meshes;
};


#endif  // !_MODEL_COMPONENT_H_
