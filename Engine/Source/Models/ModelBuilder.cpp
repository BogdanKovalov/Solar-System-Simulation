#include "ModelBuilder.h"
#include "Models/Model.h"
#include "Models/Mesh.h"
#include "ModelUtilities.h"
#include "MaterialBuilder.h"
#include "Models/ModelComponents.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::shared_ptr<ModelComponent> ModelBuilder::ImportModel(std::string PathToModel)
{
    auto FoundedModel = CreatedModels.find(PathToModel);
    if (FoundedModel != CreatedModels.end())
    {
        return FoundedModel->second;
    }

    ImportingDirectory = PathToModel.substr(0, PathToModel.find_last_of("/") + 1);

    Assimp::Importer AssimpImporter;
    aiScene const* Scene = AssimpImporter.ReadFile(PathToModel, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    assert(Scene || !(Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || Scene->mRootNode && "ASSIMP::FAILED TO READ FILE");

    CreatingModel = std::make_shared<ModelComponent>();

    ProcessNode(Scene->mRootNode, Scene);

    CreatedModels.insert(std::make_pair(PathToModel, CreatingModel));

    return CreatingModel;
}

void ModelBuilder::ProcessNode(aiNode* Node, aiScene const* Scene)
{
    if (!Node || !Scene)
    {
        return;
    }

    for (GLuint i = 0; i < Node->mNumMeshes; ++i)
    {
        aiMesh* AssimpMesh = Scene->mMeshes[Node->mMeshes[i]];
        if (AssimpMesh)
        {
            CreatingModel->Meshes.push_back(CreateMesh(AssimpMesh, Scene));
            Vertices.clear();
            Indices.clear();
            Textures.clear();
        }
    }

    for (GLuint i = 0; i < Node->mNumChildren; i++)
    {
        ProcessNode(Node->mChildren[i], Scene);
    }
}

std::shared_ptr<MeshComponent> ModelBuilder::CreateMesh(aiMesh* AssimpMesh, aiScene const* Scene)
{
    GetVertices(AssimpMesh);
    GetIndices(AssimpMesh);
    auto MeshMaterial = GetMaterial(AssimpMesh, Scene);
    std::shared_ptr<MeshComponent> NewMesh = std::make_shared<MeshComponent>();

    GLuint VAO, VBO, EBO;
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

    NewMesh->VBO = VBO;
    NewMesh->VAO = VAO;
    NewMesh->EBO = EBO;

    NewMesh->Vertices = std::move(Vertices);
    NewMesh->Indices = std::move(Indices);
    NewMesh->MeshMaterial = MeshMaterial;

    return NewMesh;
}
void ModelBuilder::GetVertices(aiMesh* AssimpMesh)
{
    if (!AssimpMesh)
    {
        return;
    }

    for (GLuint i = 0; i < AssimpMesh->mNumVertices; ++i)
    {
        Vertex NewVertex;
        NewVertex.Location = ModelUtilities::GetGLMVec(AssimpMesh->mVertices[i]);
        NewVertex.Normal = ModelUtilities::GetGLMVec(AssimpMesh->mNormals[i]);

        NewVertex.TextureCoords = glm::vec2(0.0f);
        if (AssimpMesh->mTextureCoords[0])
        {
            NewVertex.TextureCoords = ModelUtilities::GetGLMVec(AssimpMesh->mTextureCoords[0][i]);
        }
        Vertices.push_back(NewVertex);
    }
}

void ModelBuilder::GetIndices(aiMesh* AssimpMesh)
{
    if (!AssimpMesh)
    {
        return;
    }

    for (GLuint i = 0; i < AssimpMesh->mNumFaces; ++i)
    {
        aiFace Face = AssimpMesh->mFaces[i];
        for (GLuint i = 0; i < Face.mNumIndices; ++i)
        {
            Indices.push_back(Face.mIndices[i]);
        }
    }
}

std::shared_ptr<Material> ModelBuilder::GetMaterial(aiMesh* AssimpMesh, aiScene const* Scene)
{
    if (!AssimpMesh)
    {
        return std::shared_ptr<Material>();
    }

    MaterialBuilder MatBuilder{};
    return MatBuilder.CreateMaterialFromAssimpMaterial(Scene->mMaterials[AssimpMesh->mMaterialIndex], ImportingDirectory);
}