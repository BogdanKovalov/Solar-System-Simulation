#version 330 core

struct Material
{
    sampler2D TextureDiffuse1;
};

out vec4 FragColor;

in vec2 TexCoords;

uniform Material MeshMaterial;

void main()
{    
    FragColor = texture(MeshMaterial.TextureDiffuse1, TexCoords);
}