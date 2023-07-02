#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in ivec4 aBoneIds;
layout (location = 4) in vec4 aWeights;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
flat out ivec4 BoneIds;
out vec4 Weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	
	gl_Position = projection * view * vec4(FragPos, 1.0);
	TexCoord = aTexCoord;
	
	BoneIds = aBoneIds;
	Weights = aWeights;
}