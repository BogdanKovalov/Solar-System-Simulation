#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

class Shader;
class Mesh;

#include <vector>
#include <memory>

#include "Mesh.h"

class Model
{
public:
    Model(){};

    inline void AddMesh(std::shared_ptr<Mesh> NewMesh) { Meshes.push_back(NewMesh); }
    void Draw(Shader& Shader);

private:
    std::vector<std::shared_ptr<Mesh>> Meshes;
};

#endif
