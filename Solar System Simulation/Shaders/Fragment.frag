#version 330 core 

struct Material 
{
	sampler2D Diffuse;
	sampler2D Specular;
	sampler2D Emission;
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

struct SpotLightProperties
{
	vec3 Location;
	vec3 Direction;
	float CutOff;
	float OuterCutOff;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

in vec3 ourColor;
in vec2 textureCoord;
in vec3 Normal;
in vec3 FragmentPos;

uniform PointLightProperties PointLight;
uniform SpotLightProperties SpotLight;
uniform vec3 ViewPos;

uniform Material MeshMaterial;

out vec4 color;

vec4 GetPointLightInfluence(const PointLightProperties Light)
{
	vec3 AmbientComponent = vec3(texture(MeshMaterial.Diffuse, textureCoord))  * Light.Ambient * 0.3f;

	vec3 LightDirection = normalize(Light.Location - FragmentPos);
	float DiffuseStrenght = max(dot(LightDirection, normalize(Normal)), 0.0f);
	vec3 DiffuseComponent = vec3(texture(MeshMaterial.Diffuse, textureCoord)) * DiffuseStrenght * Light.Diffuse;

	vec3 ViewDirection = normalize(ViewPos - FragmentPos);
	vec3 ReflectDirection = reflect(-LightDirection, normalize(Normal));
	float SpecularStrenght = pow(max(dot(ViewDirection, ReflectDirection), 0.0f), MeshMaterial.Shininess);
	vec3 SpecularComponent = SpecularStrenght * vec3(texture(MeshMaterial.Specular, textureCoord)) * Light.Specular;

	float EmissionStrenght = floor(1 - length(vec3(texture(MeshMaterial.Specular, textureCoord))));

	float Distance = length(Light.Location - FragmentPos);
	float Attenuation = 1 / (1 + Distance * Light.LinearCoef + pow(Distance,2) * Light.QuadraticCoef);

	AmbientComponent *= Attenuation;
	DiffuseComponent *= Attenuation;
	SpecularComponent *= Attenuation;

	return vec4(AmbientComponent + DiffuseComponent + SpecularComponent + EmissionStrenght * vec3(texture(MeshMaterial.Emission, textureCoord)), 0.0f);
}

vec4 GetSpotLightInfluence()
{
	vec3 LightDirection = normalize(SpotLight.Location - FragmentPos);
	float Theta = dot(LightDirection, normalize(-SpotLight.Direction));
	float Epsilon = SpotLight.CutOff - SpotLight.OuterCutOff;
	float Intencity = clamp((Theta - SpotLight.OuterCutOff) / Epsilon, 0.0, 1.0);
	if (Theta > SpotLight.OuterCutOff)
	{
		vec3 AmbientComponent = vec3(texture(MeshMaterial.Diffuse, textureCoord))  * SpotLight.Ambient * 0.3f;

		float DiffuseStrenght = max(dot(LightDirection, normalize(Normal)), 0.0f);
		vec3 DiffuseComponent = vec3(texture(MeshMaterial.Diffuse, textureCoord)) * DiffuseStrenght * SpotLight.Diffuse;

		vec3 ViewDirection = normalize(ViewPos - FragmentPos);
		vec3 ReflectDirection = reflect(-LightDirection, normalize(Normal));
		float SpecularStrenght = pow(max(dot(ViewDirection, ReflectDirection), 0.0f), MeshMaterial.Shininess);
		vec3 SpecularComponent = SpecularStrenght * vec3(texture(MeshMaterial.Specular, textureCoord)) * SpotLight.Specular;

		DiffuseComponent *= Intencity;
		SpecularComponent *= Intencity;

		return vec4(AmbientComponent + DiffuseComponent + SpecularComponent, 0.0f);
	}
	else
	{
		return vec4(vec3(texture(MeshMaterial.Diffuse, textureCoord))  * SpotLight.Ambient * 0.3f, 0.0f);
	}

}

void main() 
{
	vec4 PointLigthComponent = GetPointLightInfluence(PointLight);
	vec4 SpotLightComponent = GetSpotLightInfluence();

	color = SpotLightComponent; //* mix(texture(Texture1, textureCoord), texture(Texture2, textureCoord), 0.5f);
}