#pragma once
#ifndef _MODEL_BUILDER_H_
#define _MODEL_BUILDER_H_

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

struct Texture;
struct Vertex;
class Model;
class Mesh;
class Material;
class Shader;
struct MeshComponent;
struct ModelComponent;

struct aiNode;
struct aiScene;
struct aiMesh;

typedef unsigned int GLuint;

class ModelBuilder
{
public:
    ModelBuilder() = delete;
    ModelBuilder(std::shared_ptr<Shader> InDefaultShader) : DefaultShader(InDefaultShader){};
    std::shared_ptr<ModelComponent> ImportModel(std::string PathToModel);

private:
    std::string ImportingDirectory;
    std::shared_ptr<ModelComponent> CreatingModel;
    std::shared_ptr<Shader> DefaultShader;

    std::vector<Vertex> Vertices;
    std::vector<GLuint> Indices;
    std::vector<Texture> Textures;

    std::unordered_map<std::string, std::shared_ptr<ModelComponent>> CreatedModels;

private:
    void ProcessNode(aiNode* Node, aiScene const* Scene);
    std::shared_ptr<MeshComponent> CreateMesh(aiMesh* AssimpMesh, aiScene const* Scene);
    
    void GetVertices(aiMesh* AssimpMesh);
    void GetIndices(aiMesh* AssimpMesh);
    std::shared_ptr<Material> GetMaterial(aiMesh* AssimpMesh, aiScene const* Scene);
};

#endif