#pragma once
#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

#include "../ModelUtilities.h"

class Material;

typedef unsigned int GLuint;
class Shader;

class Mesh
{
public:
    Mesh(std::vector<Vertex> InVertices, std::vector<GLuint> InIndices, std::shared_ptr<Material> MeshMaterial);
    void Draw(Shader& Shader);

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<Vertex> Vertices;
    // std::vector<Texture> Textures;
    std::shared_ptr<Material> MeshMaterial;
    std::vector<GLuint> Indices;

private:
    void SetupMesh();
};

#endif
