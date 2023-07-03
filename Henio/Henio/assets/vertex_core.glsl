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

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];

void main()
{
	BoneIds = aBoneIds;
	Weights = aWeights;
	
	mat4 BoneTransform = bones[aBoneIds[0]] * aWeights[0];
	BoneTransform += bones[aBoneIds[1]] * aWeights[1];
	BoneTransform += bones[aBoneIds[2]] * aWeights[2];
	BoneTransform += bones[aBoneIds[3]] * aWeights[3];
	
	vec4 PosL = BoneTransform * vec4(aPos, 1.0);
	
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	
	gl_Position = projection * view * model * PosL;
	TexCoord = aTexCoord;
}