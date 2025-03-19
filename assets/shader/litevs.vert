#version 330 core//shader
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in int am_BoneIDs[4];
layout (location = 6) in float am_Weights[4];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;  //世界坐标转换
	TexCoords = aTexCoords;
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = projection * view * vec4(FragPos, 1.0);
}
