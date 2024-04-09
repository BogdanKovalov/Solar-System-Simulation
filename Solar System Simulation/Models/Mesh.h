#pragma once
#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>

typedef unsigned int GLuint;
class Shader;

enum class ETextureType
{
    DIFFUSE,
    SPECULAR
};

std::string TypeToString(ETextureType Type);

struct Vertex
{
	glm::vec3 Location;
    glm::vec3 Normal;
    glm::vec2 TextureCoords;
};

struct Texture
{
    unsigned int ID;
    ETextureType Type;
    std::string Path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> const& InVertices, std::vector<GLuint> const& InIndices, std::vector<Texture> InTextures);
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
