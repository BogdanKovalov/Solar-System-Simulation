#include "Model.h"
#include "Mesh.h"

void Model::Draw() 
{
    for (GLuint i = 0; i < Meshes.size(); ++i)
    {
        if (!Meshes[i])
        {
            continue;
        }
        Meshes[i]->Draw();
    }
}