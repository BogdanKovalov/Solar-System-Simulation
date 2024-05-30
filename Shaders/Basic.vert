#version 330 core
layout (location = 0) in vec3 InPos;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InTextureCoords;

out vec2 TextureCoord;
out vec3 FragmentPos;
out vec3 Normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

void main()
{
    TextureCoord = InTextureCoords;
    Normal = normalize(NormalMatrix * InNormal);
    FragmentPos = vec3(ModelMatrix * vec4(InPos, 1.0));
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(InPos, 1.0);
}