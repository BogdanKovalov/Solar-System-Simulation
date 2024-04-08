#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texturePos;
layout(location = 2) in vec3 InNormal;

out vec2 textureCoord;
out vec3 Normal;
out vec3 FragmentPos;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(position, 1.0);
	textureCoord = vec2(texturePos.x, texturePos.y);
	Normal = NormalMatrix * InNormal;
	FragmentPos = vec3(ModelMatrix * vec4(position, 1.0));
}