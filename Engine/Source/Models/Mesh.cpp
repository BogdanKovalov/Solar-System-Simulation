#include "Mesh.h"
#include "../Shader.h"
#include "Material.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(std::vector<Vertex> InVertices, std::vector<GLuint> InIndices, std::shared_ptr<Material> MeshMaterial)
{
    Vertices = InVertices;
    Indices = InIndices;
    this->MeshMaterial = MeshMaterial;

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

//void Mesh::Draw()
//{
//    if (!MeshMaterial)
//    {
//        return;
//    }
//    GLuint NumLoadedTextures = 0;
//
//    MeshMaterial->LoadTexturesToShader();
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//
//    glActiveTexture(GL_TEXTURE0);
//}
//
//std::shared_ptr<Shader> Mesh::GetMaterialShader() const
//{
//    return MeshMaterial->GetShader();
//}
