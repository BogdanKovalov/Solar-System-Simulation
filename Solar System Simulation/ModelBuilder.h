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

struct aiNode;
struct aiScene;
struct aiMesh;

typedef unsigned int GLuint;

class ModelBuilder
{
public:
    std::shared_ptr<Model> ImportModel(std::string PathToModel);

private:
    std::string ImportingDirectory;
    std::shared_ptr<Model> CreatingModel;

    std::vector<Vertex> Vertices;
    std::vector<GLuint> Indices;
    std::vector<Texture> Textures;

    std::unordered_map<std::string, std::shared_ptr<Model>> CreatedModels;

private:
    void ProcessNode(aiNode* Node, aiScene const* Scene);
    std::shared_ptr<Mesh> CreateMesh(aiMesh* AssimpMesh, aiScene const* Scene);
    
    void GetVertices(aiMesh* AssimpMesh);
    void GetIndices(aiMesh* AssimpMesh);
    void GetTextures(aiMesh* AssimpMesh, aiScene const* Scene);
};

#endif