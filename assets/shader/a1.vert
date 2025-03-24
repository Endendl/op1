#version 330 core
layout (location = 0) in vec3 aPos;       // 顶点位置
layout (location = 1) in vec3 aNormal;    // 顶点法线
layout (location = 2) in vec2 aTexCoords; // 纹理坐标
layout (location = 5) in ivec4 aBoneIDs;  // 骨骼索引（最多4个）
layout (location = 6) in vec4 aWeights;   // 骨骼权重（最多4个）

out vec3 FragPos;     // 片段在世界空间中的位置
out vec3 Normal;      // 法线
out vec2 TexCoords;   // 纹理坐标

uniform mat4 model;      // 模型矩阵
uniform mat4 view;       // 视图矩阵
uniform mat4 projection; // 投影矩阵
uniform mat4 finalBonesMatrices[100]; // 骨骼变换矩阵数组（假设最多100个骨骼）

void main()
{
    // 初始化变换矩阵
    mat4 boneTransform = mat4(0.0);
    
    // 计算骨骼变换矩阵
    for (int i = 0; i < 4; i++) {
        if (aBoneIDs[i] >= 0) { // 检查骨骼索引是否有效
            boneTransform += finalBonesMatrices[aBoneIDs[i]] * aWeights[i];
        }
    }
    
    // 如果顶点不受骨骼影响，使用单位矩阵
    if (aBoneIDs[0] == -1) {
        boneTransform = mat4(1.0);
    }
    
    // 将顶点位置转换到世界空间（应用骨骼变换）
    vec4 pos = boneTransform * vec4(aPos, 1.0);
    FragPos = vec3(model * pos);
    
    // 将法线转换到世界空间（应用骨骼变换）
    vec4 norm = boneTransform * vec4(aNormal, 0.0);
    Normal = mat3(transpose(inverse(model))) * vec3(norm);
    
    
    // 传递纹理坐标
    TexCoords = aTexCoords;
    
    // 将顶点位置转换到裁剪空间
    gl_Position = projection * view * model * pos;
}