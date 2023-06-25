#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	
	float k0, k1, k2;
	
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float k0, k1, k2;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

//uniform sampler2D texture1;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform Material material;

uniform DirLight dirLight;

#define MAX_POINT_LIGHTS 10
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int nPointLights;

#define MAX_SPOT_LIGHTS 5
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int nSpotLights;

uniform vec3 viewPos; 

vec3 CalcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcDirLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 diffMap = vec3(texture(diffuse0, TexCoord));
	vec3 specMap = vec3(texture(specular0, TexCoord));
	
	vec3 result;
	
	// directional light
	result = CalcDirLight(norm, viewDir, diffMap, specMap);
	
	// point lights
	for (int i = 0; i < nPointLights; i++)
	{
		result += CalcPointLight(i, norm, viewDir, diffMap, specMap);
	}
	
	// spot lights
	for (int i = 0; i < nSpotLights; i++)
	{
		result += CalcSpotLight(i, norm, viewDir, diffMap, specMap);
	}
	
	result = clamp(result, 0.0, 1.0);
	FragColor = vec4(result, 1.0);
}

vec3 CalcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
	vec3 lightDir = normalize(spotLights[idx].position - FragPos);
	float theta = dot(lightDir, normalize(-spotLights[idx].direction));
	
	// ambient
	vec3 ambient = spotLights[idx].ambient * diffMap;
	
	if (theta > spotLights[idx].outerCutOff)
	{
		// if in cutoff, render light
		
		//diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = spotLights[idx].diffuse * (diff * diffMap);
		
		//specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
		vec3 specular = spotLights[idx].specular * (spec * specMap);
		
		float intensity = (theta - spotLights[idx].outerCutOff) / (spotLights[idx].cutOff - spotLights[idx].outerCutOff);
		intensity = clamp(intensity, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		float dist = length(spotLights[idx].position - FragPos);
		float attenuation = 1.0 / (spotLights[idx].k0 + spotLights[idx].k1 * dist + spotLights[idx].k2 * (dist * dist));
		
		return vec3(ambient + diffuse + specular) * attenuation;
	}
	
	return ambient;
}

vec3 CalcDirLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
	// ambient 
	vec3 ambient = dirLight.ambient * diffMap;
	
	//diffuse
	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = dirLight.diffuse * (diff * diffMap);
	
	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = dirLight.specular * (spec * specMap);
	
	return vec3(ambient + diffuse + specular);
}

vec3 CalcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
	//ambient
	vec3 ambient = pointLights[idx].ambient * diffMap;

	//diffuse
	vec3 lightDir = normalize(pointLights[idx].position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLights[idx].diffuse * (diff * diffMap);

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = pointLights[idx].specular * (spec * specMap);
	
	float dist = length(pointLights[idx].position - FragPos);
	float attenuation = 1.0 / (pointLights[idx].k0 + pointLights[idx].k1 * dist + pointLights[idx].k2 * (dist * dist));

	return vec3(ambient + diffuse + specular) * attenuation;
}