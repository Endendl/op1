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
	glm::mat4 transformation; // �ڵ�ı任���󣨾ֲ������ڵ�ı任��
	std::string name; // �ڵ�����
	int childrenCount; // �ӽڵ�����
	std::vector<AssimpNodeData> children; // �ӽڵ��б�
};

class animation
{
public:
	animation() = default;

	animation(std::string& animationPath, model* _model)
	{ // ʹ��Assimp���ض����ļ�
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
		assert(scene && scene->mRootNode); // ȷ�������͸��ڵ����
		auto animation = scene->mAnimations[0];
		m_Duration = animation->mDuration;// �������ܳ���ʱ�䣨��ticksΪ��λ��
		m_TicksPerSecond = animation->mTicksPerSecond;// ÿ���ticks����֡�ʣ�
		// ��ȡ���ڵ��ȫ�ֱ任���󣬲������������
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
		globalTransformation = globalTransformation.Inverse();
		
		ReadHierarchyData(m_RootNode, scene->mRootNode);// ��ȡ�����㼶�ṹ
		ReadMissingBones(animation, *_model);// ��ȡ�����еĹ������ݣ�����ģ���еĹ�����Ϣ����ƥ��
	}

	~animation()
	{
	}

	Bone* FindBone(const std::string& name) // ��m_Bones�в���ָ�����ƵĹ���
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


	inline float GetTicksPerSecond() { return m_TicksPerSecond; }//���ض�����֡��
	inline float GetDuration() { return m_Duration; }//���ض������ܳ���ʱ��
	inline const AssimpNodeData& GetRootNode() { return m_RootNode; }//���ع����㼶�ṹ�ĸ��ڵ㡣
	inline const std::map<std::string, BoneInfo>& GetBoneIDMap()
	{//���ع������Ƶ�������Ϣ��ӳ�䡣
		return m_BoneInfoMap;
	}
	
private:
	void ReadMissingBones(const aiAnimation* animation, model& _model)
	{
		int size = animation->mNumChannels;// ��ȡ�����еĹ�������
		// ��ȡģ���еĹ�����Ϣӳ��͹���������
		auto& boneInfoMap = _model.GetBoneInfoMap();
		int& boneCount = _model.GetBoneCount(); 

		
		for (int i = 0; i < size; i++)
		{ // ���������еĹ�������
			auto channel = animation->mChannels[i];// ��ȡ�����Ĺؼ�֡����
			std::string boneName = channel->mNodeName.data;// ��ȡ��������

			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{// ���ģ����û�иù�������Ϣ������ӵ�boneInfoMap��
				boneInfoMap[boneName].id = boneCount;
				boneCount++;
			}
			// ����Bone���󣬲�������ӵ�m_Bones��
			m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, channel));
		}

		m_BoneInfoMap = boneInfoMap;
	}

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
	{
		assert(src);// ȷ��Դ�ڵ����

		// ��ȡ�ڵ����ƺͱ任����
		dest.name = src->mName.data;
		dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
		dest.childrenCount = src->mNumChildren;// ��ȡ�ӽڵ�����

		for (int i = 0; i < src->mNumChildren; i++)
		{// �ݹ��ȡ�ӽڵ�����
			AssimpNodeData newData;
			ReadHierarchyData(newData, src->mChildren[i]);// �ݹ��ȡ�ӽڵ�
			dest.children.push_back(newData);// ���ӽڵ���ӵ�children�б���
		}
	}
	float m_Duration;//�����ܳ���ʱ��
	int m_TicksPerSecond;//����֡��
	std::vector<Bone> m_Bones; //�洢���й����Ķ�������
	AssimpNodeData m_RootNode;//�����㼶�ṹ�ĸ��ڵ㡣
	std::map<std::string, BoneInfo> m_BoneInfoMap;//�������Ƶ�������Ϣ��ӳ�䣬���ڿ��ٲ��ҹ�����
};
std::vector<animation> animationslist;