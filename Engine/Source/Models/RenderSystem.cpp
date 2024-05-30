#include "RenderSystem.h"
#include "Models/ModelComponents.h"
#include "Shader.h"
#include "ShaderManager.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderSystem::Update(float DeltaTime)
{
    LoadCommonDataToShaders();

    auto ModelComponents = OwningWorld->GetAllComponents<ModelComponent>();
    for (auto ModelComponent : ModelComponents)
    {
        auto MeshMaterial = ModelComponent->Meshes[0]->MeshMaterial;
        if (!MeshMaterial)
        {
            continue;
        }
        auto MaterialShader = GetShaderByType(MeshMaterial->GetShaderType());

        if (!MaterialShader)
        {
            continue;    
        }

        LoadPositionDataToShader(MaterialShader, ModelComponent->PosComponent);

        auto MeshComponents = ModelComponent->Meshes;
        for (auto MeshComponent : MeshComponents)
        {
            DrawMesh(MeshComponent, MaterialShader);
        }
    }
}

void RenderSystem::LoadCommonDataToShaders() const
{
    if (!OwningWorld)
    {
        return;
    }

    auto CameraComponents = OwningWorld->GetAllComponents<CameraComponent>();
    CameraComponent* MainCamera = CameraComponents[0];
    if (!MainCamera)
    {
        return;
    }
    auto Shaders = OwningWorld->GetAllComponents<Shader>();

    glm::mat4 ProjectionMatrix(1.0f);
    ProjectionMatrix = glm::perspective(
        glm::radians(MainCamera->FieldOfView), 1080.0f / 1920.0f, MainCamera->NearPlaneDistance, MainCamera->FarPlaneDistance);

    glm::mat4 VectorMatrix = glm::mat4(glm::vec4(MainCamera->RightVector, 0.0f), glm::vec4(MainCamera->UpVector, 0.0f),
        glm::vec4(MainCamera->ForwardVector, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 PositionMatrix(1.0f);
    PositionMatrix = glm::translate(PositionMatrix, -MainCamera->PosComponent->Location);

    glm::mat4 ViewMatrix = glm::transpose(VectorMatrix) * PositionMatrix;

    for (auto Shader : Shaders)
    {
        Shader->SetMatrix4("ProjectionMatrix", glm::value_ptr(ProjectionMatrix));
        Shader->SetMatrix4("ViewMatrix", glm::value_ptr(ViewMatrix));
        Shader->SetVec3("ViewPos", MainCamera->PosComponent->Location);
    }
}

void RenderSystem::LoadPositionDataToShader(Shader const* UsingShader, std::shared_ptr<PositionComponent> const PosComponent) const
{
    if (!UsingShader || !PosComponent)
    {
        return;
    }

    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, PosComponent->Location);
    ModelMatrix = glm::scale(ModelMatrix, PosComponent->Scale);
    UsingShader->SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));

    glm::mat3 NormalMatrix = glm::mat3(glm::transpose(glm::inverse(ModelMatrix)));
    UsingShader->SetMatrix3("NormalMatrix", glm::value_ptr(NormalMatrix));
}

void RenderSystem::DrawMesh(std::shared_ptr<MeshComponent> const Mesh, Shader const* UsingShader) const
{
    if(!Mesh->MeshMaterial)
    {
        return;
    }

    Mesh->MeshMaterial->LoadPropertiesToShader(UsingShader);
    glBindVertexArray(Mesh->VAO);
    glDrawElements(GL_TRIANGLES, Mesh->Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

Shader* RenderSystem::GetShaderByType(EShaderType Type) const
{
    auto Shaders = OwningWorld->GetAllComponents<Shader>();
    for (auto Shader : Shaders)
    {
        if (Shader->GetType() == Type)
        {
            return Shader;
        }
    }
    return nullptr;
}