#version 330 core
// 输入顶点属性
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in int am_BoneIDs[4];
layout (location = 6) in float am_Weights[4];

// 传递给片段着色器的变量
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

// Uniform变量
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// 骨骼相关常量和Uniform变量
const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

// 控制是否播放动画
uniform bool play;

void main()
{
    vec4 totalPosition = vec4(aPos, 1.0f); // 默认使用原始顶点位置
    vec3 totalNormal = aNormal;            // 默认使用原始法线

    // 如果播放动画，则应用骨骼变换
    if (play) {
        totalPosition = vec4(0.0f);
        totalNormal = vec3(0.0f);
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
            if (am_BoneIDs[i] == -1) 
                continue;
            if (am_BoneIDs[i] >= MAX_BONES) {
                totalPosition = vec4(aPos, 1.0f);
                totalNormal = aNormal;
                break;
            }
            // 变换顶点位置
            vec4 localPosition = finalBonesMatrices[am_BoneIDs[i]] * vec4(aPos, 1.0f);
            totalPosition += localPosition * am_Weights[i];

            // 变换法线
            vec3 localNormal = mat3(finalBonesMatrices[am_BoneIDs[i]]) * aNormal;
            totalNormal += localNormal * am_Weights[i];
        }
    }

    // 变换到世界空间
    FragPos = vec3(model * totalPosition);
    Normal = mat3(transpose(inverse(model))) * normalize(totalNormal); // 归一化并变换到世界空间

    // 变换到裁剪空间
    gl_Position = projection * view * model * totalPosition;
    if (gl_VertexID == 0) { // 仅打印第一个顶点的数据
        
    }

    // 传递纹理坐标
    TexCoords = aTexCoords;
}

