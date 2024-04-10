#include "Mesh.h"
#include "../Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(std::vector<Vertex> InVertices, std::vector<GLuint> InIndices, std::vector<Texture> InTextures)
{
    Vertices = InVertices;
    Indices = InIndices;
    Textures = InTextures;

    SetupMesh();
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), Indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& Shader)
{
    GLuint DiffuseNum = 1;
    GLuint SpecularNum = 1;
    GLuint NormalNum = 1;

    for (GLuint i = 0; i < Textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string Number;
        std::string Name = ModelUtilities::TypeToString(Textures[i].Type);
        if (Textures[i].Type == ETextureType::DIFFUSE)
        {
            Number = std::to_string(DiffuseNum++);
        }
        if (Textures[i].Type == ETextureType::SPECULAR)
        {
            Number = std::to_string(SpecularNum++);
        }
        if (Textures[i].Type == ETextureType::NORMAL)
        {
            Number = std::to_string(NormalNum++);
        }

        Shader.SetInt(("MeshMaterial." + Name + Number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
