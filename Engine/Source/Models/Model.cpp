#include "Model.h"
#include "Mesh.h"
#include "../Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Model::Draw() 
{
    LoadModelMatrixToShader();
    for (GLuint i = 0; i < Meshes.size(); ++i)
    {
        if (!Meshes[i])
        {
            continue;
        }
       // Meshes[i]->Draw();
    }
}

void Model::LoadModelMatrixToShader() 
{
   //// std::shared_ptr<Shader> MaterialShader = Meshes[0]->GetMaterialShader();
   // if (!MaterialShader)
   // {
   //     return;
   // }

   // glm::mat4 ModelMatrix(1.0f);
   // ModelMatrix = glm::translate(ModelMatrix, Location);
   // ModelMatrix = glm::scale(ModelMatrix, Scale);
   // MaterialShader->SetMatrix4("ModelMatrix", glm::value_ptr(ModelMatrix));

   // glm::mat3 NormalMatrix = glm::mat3(glm::transpose(glm::inverse(ModelMatrix)));
   // MaterialShader->SetMatrix3("NormalMatrix", glm::value_ptr(NormalMatrix));


}