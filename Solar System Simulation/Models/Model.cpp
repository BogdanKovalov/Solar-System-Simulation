#include "Model.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Model::Model(const char* Path)
{
    LoadModel(Path);
}

void Model::LoadModel(const char* Path)
{
    Assimp::Importer AssimpImporter;
    const aiScene* Scene = AssimpImporter.ReadFile(Path, aiProcess_Triangulate | aiProcess_FlipUVs);

    assert(Scene && "ASSIMP::FAILED TO LOAD MODEL");
    assert(!(Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || Scene->mRootNode && "ASSIMP::FAILED TO LOAD MODEL");

    std::string StringPath = static_cast<std::string>(Path);
    Directory = StringPath.substr(0, StringPath.find_last_of('/'));

    ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{
    for (GLuint i = 0; i < Node->mNumMeshes; ++i)
    {
        aiMesh* AssimpMesh = Scene->mMeshes[Node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(AssimpMesh, Scene));
    }

    for (GLuint i = 0; i < Node->mNumChildren; ++i)
    {
        ProcessNode(Node->mChildren[i], Scene);
    }
}

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* AssimpMesh, const aiScene* Scene)
{
    std::vector<Vertex> Vertices;
    std::vector<GLuint> Indices;
    std::vector<Texture> Textures;

    for (GLuint i = 0; i < AssimpMesh->mNumVertices; ++i)
    {
        Vertex NewVertex;

        glm::vec3 TempVector;
        TempVector.x = AssimpMesh->mVertices[i].x;
        TempVector.y = AssimpMesh->mVertices[i].y;
        TempVector.z = AssimpMesh->mVertices[i].z;
        NewVertex.Location = TempVector;

        TempVector.x = AssimpMesh->mNormals[i].x;
        TempVector.y = AssimpMesh->mNormals[i].y;
        TempVector.z = AssimpMesh->mNormals[i].z;
        NewVertex.Normal = TempVector;

        NewVertex.TextureCoords = glm::vec2(0.0f);
        if (AssimpMesh->mTextureCoords[0])
        {
            glm::vec2 TempVec;
            TempVec.x = AssimpMesh->mTextureCoords[0][i].x;
            TempVec.y = AssimpMesh->mTextureCoords[0][i].y;
            NewVertex.TextureCoords = TempVec;
        }
        else
        {
            NewVertex.TextureCoords = glm::vec2(0.0f);
        }
        Vertices.push_back(NewVertex);
    }

    for (GLuint i = 0; i < AssimpMesh->mNumFaces; ++i)
    {
        aiFace Face = AssimpMesh->mFaces[i];
        for (GLuint i = 0; i < Face.mNumIndices; ++i)
        {
            Indices.push_back(Face.mIndices[i]);
        }
    }

    if (AssimpMesh->mMaterialIndex >= 0)
    {
        aiMaterial* Material = Scene->mMaterials[AssimpMesh->mMaterialIndex];
        std::vector<Texture> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, ETextureType::DIFFUSE);
        Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

        std::vector<Texture> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR, ETextureType::SPECULAR);
        Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
    }

    return std::shared_ptr<Mesh>(new Mesh(Vertices, Indices, Textures));
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, ETextureType TextureType)
{
    std::vector<Texture> Textures;
    for (GLuint i = 0; i < Material->GetTextureCount(Type); ++i)
    {
        aiString String;
        Material->GetTexture(Type, i, &String);
        bool Skip = false;
        for (GLuint i = 0; i < LoadedTextures.size(); ++i)
        {
            if (std::strcmp(LoadedTextures[i].Path.data(), String.C_Str()) == 0)
            {
                Textures.push_back(LoadedTextures[i]);
                Skip = true;
                break;
            }
        }

        if (!Skip)
        {
            Texture NewTexture;
            std::string Path = Directory;
            NewTexture.ID = GenerateTexture(String.C_Str(), Directory);
            NewTexture.Type = TextureType;
            NewTexture.Path = String.C_Str();
            Textures.push_back(NewTexture);
            LoadedTextures.push_back(NewTexture);
        }
    }
    return Textures;
}

GLuint GenerateTexture(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::Draw(Shader& Shader) 
{
    for (GLuint i = 0; i < Meshes.size(); ++i)
    {
        if (!Meshes[i])
        {
            continue;
        }
        Meshes[i]->Draw(Shader);
    }
}