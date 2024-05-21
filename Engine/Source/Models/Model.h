#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

class Shader;
class Mesh;
struct MeshComponent;

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Mesh.h"

class Model
{
public:
    Model() : Location(glm::vec3(0.0f)), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)){};

    inline void AddMesh(std::shared_ptr<MeshComponent> NewMesh) { Meshes.push_back(NewMesh); }
    void Draw();

    void SetLocation(glm::vec3 NewLocation) { Location = NewLocation; }
    void SetScale(glm::vec3 NewScale) { Scale = NewScale; }

    inline glm::vec3 GetLocation() const { return Location; }
    inline glm::vec3 GetScale() const { return Scale; }

    std::vector<std::shared_ptr<MeshComponent>> Meshes;

    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;

private:
    void LoadModelMatrixToShader();
};

#endif
