#include "RenderSystem.h"
#include "Models/ModelComponents.h"
#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderSystem::Update(float DeltaTime)
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

    glm::mat4 VectorMatrix = glm::mat4(
        glm::vec4(MainCamera->RightVector, 0.0f), glm::vec4(MainCamera->UpVector, 0.0f), glm::vec4(MainCamera->ForwardVector, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 PositionMatrix(1.0f);
    PositionMatrix = glm::translate(PositionMatrix, -MainCamera->PosComponent->Location);

    glm::mat4 ViewMatrix = glm::transpose(VectorMatrix) * PositionMatrix;




    auto ModelComponents = OwningWorld->GetAllComponents<ModelComponent>();

    for (auto ModelComponent : ModelComponents)
    {
        auto MeshMaterial = ModelComponent->Meshes[0]->MeshMaterial;
        if (!MeshMaterial)
        {
            return;
        }
        auto MaterialShader = MeshMaterial->GetShader();
        glm::mat4 ModelMatrix(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, ModelComponent->PosComponent->Location);
        ModelMatrix = glm::scale(ModelMatrix, ModelComponent->PosComponent->Scale);
        MaterialShader->SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));

        glm::mat3 NormalMatrix = glm::mat3(glm::transpose(glm::inverse(ModelMatrix)));
        MaterialShader->SetMatrix3("NormalMatrix", glm::value_ptr(NormalMatrix));

        auto MeshComponents = ModelComponent->Meshes;
        for (auto MeshComponent : MeshComponents)
        {
            if (!MeshComponent->MeshMaterial)
            {
                return;
            }
            GLuint NumLoadedTextures = 0;

            MeshComponent->MeshMaterial->LoadTexturesToShader();
            glBindVertexArray(MeshComponent->VAO);
            glDrawElements(GL_TRIANGLES, MeshComponent->Indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glActiveTexture(GL_TEXTURE0);
        }
    }
}