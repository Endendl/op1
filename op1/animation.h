#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "bone.h"
#include <functional>
#include "animdata.h"
#include "model.h"

struct AssimpNodeData
{
	glm::mat4 transformation; // 节点的变换矩阵（局部到父节点的变换）
	std::string name; // 节点名称
	int childrenCount; // 子节点数量
	std::vector<AssimpNodeData> children; // 子节点列表
};

class animation
{
public:
	animation() = default;

	animation(std::string& animationPath, model* _model)
	{ // 使用Assimp加载动画文件
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
		assert(scene && scene->mRootNode); // 确保场景和根节点存在
		auto animation = scene->mAnimations[0];
		m_Duration = animation->mDuration;// 动画的总持续时间（以ticks为单位）
		m_TicksPerSecond = animation->mTicksPerSecond;// 每秒的ticks数（帧率）
		// 获取根节点的全局变换矩阵，并计算其逆矩阵
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
		globalTransformation = globalTransformation.Inverse();
		
		ReadHierarchyData(m_RootNode, scene->mRootNode);// 读取骨骼层级结构
		ReadMissingBones(animation, *_model);// 读取动画中的骨骼数据，并与模型中的骨骼信息进行匹配
	}

	~animation()
	{
	}

	Bone* FindBone(const std::string& name) // 在m_Bones中查找指定名称的骨骼
	{
		auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
			[&](const Bone& Bone)
			{
				return Bone.GetBoneName() == name;
			}
		);
		if (iter == m_Bones.end()) return nullptr;
		else return &(*iter);
	}


	inline float GetTicksPerSecond() { return m_TicksPerSecond; }//返回动画的帧率
	inline float GetDuration() { return m_Duration; }//返回动画的总持续时间
	inline const AssimpNodeData& GetRootNode() { return m_RootNode; }//返回骨骼层级结构的根节点。
	inline const std::map<std::string, BoneInfo>& GetBoneIDMap()
	{//返回骨骼名称到骨骼信息的映射。
		return m_BoneInfoMap;
	}
	
private:
	void ReadMissingBones(const aiAnimation* animation, model& _model)
	{
		int size = animation->mNumChannels;// 获取动画中的骨骼数量
		// 获取模型中的骨骼信息映射和骨骼计数器
		auto& boneInfoMap = _model.GetBoneInfoMap();
		int& boneCount = _model.GetBoneCount(); 

		
		for (int i = 0; i < size; i++)
		{ // 遍历动画中的骨骼数据
			auto channel = animation->mChannels[i];// 获取骨骼的关键帧数据
			std::string boneName = channel->mNodeName.data;// 获取骨骼名称

			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{// 如果模型中没有该骨骼的信息，则添加到boneInfoMap中
				boneInfoMap[boneName].id = boneCount;
				boneCount++;
			}
			// 创建Bone对象，并将其添加到m_Bones中
			m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, channel));
		}

		m_BoneInfoMap = boneInfoMap;
	}

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
	{
		assert(src);// 确保源节点存在

		// 读取节点名称和变换矩阵
		dest.name = src->mName.data;
		dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
		dest.childrenCount = src->mNumChildren;// 获取子节点数量

		for (int i = 0; i < src->mNumChildren; i++)
		{// 递归读取子节点数据
			AssimpNodeData newData;
			ReadHierarchyData(newData, src->mChildren[i]);// 递归读取子节点
			dest.children.push_back(newData);// 将子节点添加到children列表中
		}
	}
	float m_Duration;//动画总持续时间
	int m_TicksPerSecond;//动画帧率
	std::vector<Bone> m_Bones; //存储所有骨骼的动画数据
	AssimpNodeData m_RootNode;//骨骼层级结构的根节点。
	std::map<std::string, BoneInfo> m_BoneInfoMap;//骨骼名称到骨骼信息的映射，用于快速查找骨骼。
};
std::vector<animation> animationslist;