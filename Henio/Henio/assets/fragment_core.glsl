#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
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

struct DirLight
{
	vec3 direction;

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

uniform Material material;

uniform SpotLight spotLight;
uniform PointLight pointLight;
uniform DirLight dirLight;

uniform vec3 viewPos; 

vec3 CalcSpotLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcDirLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 CalcPointLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 diffMap = vec3(texture(material.diffuse, TexCoord));
	vec3 specMap = vec3(texture(material.specular, TexCoord));
	
	FragColor = vec4(CalcSpotLight(norm, viewDir, diffMap, specMap), 1.0);
}

vec3 CalcSpotLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
	vec3 lightDir = normalize(spotLight.position - FragPos);
	float theta = dot(lightDir, normalize(-spotLight.direction));
	
	// ambient
	vec3 ambient = spotLight.ambient * diffMap;
	
	if (theta > spotLight.outerCutOff)
	{
		// if in cutoff, render light
		
		//diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = spotLight.diffuse * (diff * diffMap);
		
		//specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
		vec3 specular = spotLight.specular * (spec * specMap);
		
		float intensity = (theta - spotLight.outerCutOff) / (spotLight.cutOff - spotLight.outerCutOff);
		intensity = clamp(intensity, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		float dist = length(spotLight.position - FragPos);
		float attenuation = 1.0 / (spotLight.k0 + spotLight.k1 * dist + spotLight.k2 * (dist * dist));
		
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

vec3 CalcPointLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
	//ambient
	vec3 ambient = pointLight.ambient * diffMap;

	//diffuse
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLight.diffuse * (diff * diffMap);

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = pointLight.specular * (spec * specMap);
	
	float dist = length(pointLight.position - FragPos);
	float attenuation = 1.0 / (pointLight.k0 + pointLight.k1 * dist + pointLight.k2 * (dist * dist));

	return vec3(ambient + diffuse + specular) * attenuation;
}