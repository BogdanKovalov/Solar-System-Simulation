#version 330 core 

in vec3 ourColor;
in vec2 textureCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float MixCoef;

out vec4 color;


void main() 
{
	color = mix(texture(Texture1, textureCoord), texture(Texture2, vec2(textureCoord.x, textureCoord.y)), MixCoef);
}