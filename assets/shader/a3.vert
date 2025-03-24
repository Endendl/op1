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
    // 初始化顶点位置和法线
    vec4 totalPosition = vec4(aPos, 1.0f); // 默认使用原始顶点位置
    vec3 totalNormal = aNormal;            // 默认使用原始法线

    // 如果播放动画，则应用骨骼变换
    if (play) {
        mat4 boneTransform = mat4(0.0f); // 初始化骨骼变换矩阵

        // 计算骨骼变换矩阵
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
            if (am_BoneIDs[i] == -1 || am_Weights[i] == 0.0) {
                continue; // 跳过无效的骨骼 ID 或权重为 0 的情况
            }
            if (am_BoneIDs[i] >= MAX_BONES) {
                // 骨骼 ID 超出范围，使用原始顶点位置和法线
                totalPosition = vec4(aPos, 1.0f);
                totalNormal = aNormal;
                break;
            }
            // 累加骨骼变换矩阵
            boneTransform += finalBonesMatrices[am_BoneIDs[i]] * am_Weights[i];
        }

        // 应用骨骼变换到顶点位置和法线
        totalPosition = boneTransform * totalPosition;
        totalNormal = mat3(boneTransform) * totalNormal;
    }

    // 变换到世界空间
    FragPos = vec3(model * totalPosition);
    Normal = mat3(transpose(inverse(model))) * normalize(totalNormal); // 归一化并变换到世界空间

    // 变换到裁剪空间
    gl_Position = projection * view * model * totalPosition;

    // 传递纹理坐标
    TexCoords = aTexCoords;
}