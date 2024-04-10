#include "ModelBuilder.h"
#include "Models/Model.h"
#include "Models/Mesh.h"
#include "ModelUtilities.h"
#include "TextureBuilder.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cassert>

std::shared_ptr<Model> ModelBuilder::ImportModel(std::string PathToModel)
{
    auto FoundedModel = CreatedModels.find(PathToModel);
    if (FoundedModel != CreatedModels.end())
    {
        return FoundedModel->second;
    }

    ImportingDirectory = PathToModel.substr(0, PathToModel.find_last_of("/") + 1);

    Assimp::Importer AssimpImporter;
    aiScene const* Scene = AssimpImporter.ReadFile(PathToModel, aiProcess_Triangulate | aiProcess_FlipUVs);

    assert(Scene || !(Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || Scene->mRootNode && "ASSIMP::FAILED TO READ FILE");

    CreatingModel = std::shared_ptr<Model>(new Model);

    ProcessNode(Scene->mRootNode, Scene);

    CreatedModels.insert(std::make_pair(PathToModel, CreatingModel));

    return CreatingModel;
}

void ModelBuilder::ProcessNode(aiNode* Node, aiScene const* Scene)
{
    for (GLuint i = 0; i < Node->mNumMeshes; ++i)
    {
        aiMesh* AssimpMesh = Scene->mMeshes[Node->mMeshes[i]];
        if (AssimpMesh)
        {
            CreatingModel->AddMesh(CreateMesh(AssimpMesh, Scene));
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

std::shared_ptr<Mesh> ModelBuilder::CreateMesh(aiMesh* AssimpMesh, aiScene const* Scene)
{
    GetVertices(AssimpMesh);
    GetIndices(AssimpMesh);
    GetTextures(AssimpMesh, Scene);
    return std::shared_ptr<Mesh>(new Mesh(Vertices, Indices, Textures));
}
void ModelBuilder::GetVertices(aiMesh* AssimpMesh)
{
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
    for (GLuint i = 0; i < AssimpMesh->mNumFaces; ++i)
    {
        aiFace Face = AssimpMesh->mFaces[i];
        for (GLuint i = 0; i < Face.mNumIndices; ++i)
        {
            Indices.push_back(Face.mIndices[i]);
        }
    }
}

void ModelBuilder::GetTextures(aiMesh* AssimpMesh, aiScene const* Scene)
{
    TextureBuilder TexBuilder;
    if (AssimpMesh->mMaterialIndex >= 0)
    {
        aiMaterial* Material = Scene->mMaterials[AssimpMesh->mMaterialIndex];
        std::vector<Texture> DiffuseMaps =
            TexBuilder.CreateTextureFromMaterial(Material, aiTextureType_DIFFUSE, ETextureType::DIFFUSE, ImportingDirectory);
        Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

        std::vector<Texture> SpecularMaps =
            TexBuilder.CreateTextureFromMaterial(Material, aiTextureType_SPECULAR, ETextureType::SPECULAR, ImportingDirectory);
        Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());

        std::vector<Texture> NormalMaps =
            TexBuilder.CreateTextureFromMaterial(Material, aiTextureType_HEIGHT, ETextureType::NORMAL, ImportingDirectory);
        Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());
    }
}