#version 330 core

struct Material
{
    sampler2D TextureDiffuse1;
	sampler2D TextureSpecular1;
	sampler2D TextureNormal1;
	float Shininess;
};

struct PointLightProperties
{
	vec3 Location;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float LinearCoef;
	float QuadraticCoef;
};

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragmentPos;

uniform PointLightProperties PointLight;
uniform vec3 ViewPos;

uniform Material MeshMaterial;

out vec4 color;

vec4 GetPointLightInfluence(const PointLightProperties Light)
{
	vec3 AmbientComponent = vec3(texture(MeshMaterial.TextureDiffuse1, TextureCoord))  * Light.Ambient;

	vec3 LightDirection = normalize(Light.Location - FragmentPos);
	vec3 Normal = texture(MeshMaterial.TextureNormal1, TextureCoord).rgb;
	Normal = normalize(Normal * 2.0 - 1.0);
	float DiffuseStrenght = max(dot(LightDirection, Normal), 0.0f);
	vec3 DiffuseComponent = vec3(texture(MeshMaterial.TextureDiffuse1, TextureCoord)) * DiffuseStrenght * Light.Diffuse;

	vec3 ViewDirection = normalize(ViewPos - FragmentPos);
	vec3 ReflectDirection = reflect(-LightDirection, Normal);
	float SpecularStrenght = pow(max(dot(ViewDirection, ReflectDirection), 0.0f), MeshMaterial.Shininess);
	vec3 SpecularComponent = SpecularStrenght * vec3(texture(MeshMaterial.TextureSpecular1, TextureCoord)) * Light.Specular;

	float Distance = length(Light.Location - FragmentPos);
	float Attenuation = 1 / (1 + Distance * Light.LinearCoef + pow(Distance,2) * Light.QuadraticCoef);

	AmbientComponent *= Attenuation;
	DiffuseComponent *= Attenuation;
	SpecularComponent *= Attenuation;

	return vec4(AmbientComponent + DiffuseComponent + SpecularComponent, 0.0f);
}

void main() 
{
	vec4 PointLigthComponent = GetPointLightInfluence(PointLight);
	//vec4 SpotLightComponent = GetSpotLightInfluence();

	color = PointLigthComponent;
}