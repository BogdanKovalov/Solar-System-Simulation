#pragma once
#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "../ModelUtilities.h"

typedef unsigned int GLuint;
class Shader;

class Mesh
{
public:
    Mesh(std::vector<Vertex> InVertices, std::vector<GLuint> InIndices, std::vector<Texture> InTextures);
    void Draw(Shader& Shader);

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    std::vector<Vertex> Vertices;
    std::vector<Texture> Textures;
    std::vector<GLuint> Indices;

   private:
    void SetupMesh();
};

#endif
