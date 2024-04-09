#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

class Shader;
class Mesh;
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;
struct Texture;

#include <vector>
#include <string>
#include <memory>

#include "Mesh.h"


GLuint GenerateTexture(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    Model(const char* Path);
    void Draw(Shader& Shader);

private:
    std::vector<std::shared_ptr<Mesh>> Meshes;
    std::vector<Texture> LoadedTextures;
    std::string Directory;

private:
    void LoadModel(const char* Path);
    void ProcessNode(aiNode* Node, const aiScene* Scene);
    std::shared_ptr<Mesh> ProcessMesh(aiMesh* AssimpMesh, const aiScene* Scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, ETextureType TextureType);
};

#endif
