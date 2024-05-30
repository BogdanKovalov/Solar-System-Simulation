#pragma once
#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include "ECS/World.h"
#include "Systems/ISystem.h"
#include "Shader.h"

struct PositionComponent;
struct MeshComponent;

class RenderSystem : public ISystem
{
public:
    virtual void Update(float DeltaTime) override;

private:
    void LoadCommonDataToShaders() const;
    void LoadPositionDataToShader(Shader const* UsingShader, std::shared_ptr<PositionComponent> const PosComponent) const;
    void DrawMesh(std::shared_ptr<MeshComponent> const Mesh, Shader const* UsingShader) const;
    Shader* GetShaderByType(EShaderType Type) const;
};

#endif
