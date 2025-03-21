#pragma once
#include "mounting.h"
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "animation.h"
#include "bone.h"
class animator :
    public mounting
{
public:
	animator()
	{
		name = "animator";
		m_CurrentTime = 0.0;
		//m_CurrentAnimation = animation;
		m_FinalBoneMatrices.reserve(100);

		for (int i = 0; i < 100; i++)
			m_FinalBoneMatrices.push_back(glm::mat4(1.0f));//多了100个骨头
	}

	virtual void setint(std::string _type, int mod) {}
	virtual void setbool(std::string _type, bool mod) {}
	virtual void setfloat(std::string _type, float mod) {}
	void UpdateAnimation(float dt)
	{
		m_DeltaTime = dt;
		if (m_CurrentAnimation)
		{
			//std::cout << "UpdateAnimation" << std::endl;
			m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
			m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
			CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
		}
	}

	void PlayAnimation(animation* pAnimation)
	{
		std::cout << "PlayAnimation" << std::endl;
		m_CurrentAnimation = pAnimation;
		m_CurrentTime = 0.0f;
	}

	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
	{
		std::string nodeName = node->name;
		glm::mat4 nodeTransform = node->transformation;

		Bone* Bone = m_CurrentAnimation->FindBone(nodeName);

		if (Bone)
		{
			Bone->Update(m_CurrentTime);
			nodeTransform = Bone->GetLocalTransform();
		}

		glm::mat4 globalTransformation = parentTransform * nodeTransform;

		auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
		if (boneInfoMap.find(nodeName) != boneInfoMap.end())
		{
			int index = boneInfoMap[nodeName].id;
			glm::mat4 offset = boneInfoMap[nodeName].offset;
			m_FinalBoneMatrices[index] = globalTransformation * offset;

			//std::cout << "Bone: " << nodeName << ", Index: " << index << "\n";
			//std::cout << "Global Transformation:\n";
			//PrintMatrix(globalTransformation);
			//std::cout << "Offset:\n";
			//PrintMatrix(offset);
			//std::cout << "Final Bone Matrix:\n";
			//PrintMatrix(m_FinalBoneMatrices[index]);	
		}

		for (int i = 0; i < node->childrenCount; i++)
			CalculateBoneTransform(&node->children[i], globalTransformation);
	}

	std::vector<glm::mat4> GetFinalBoneMatrices()
	{
		return m_FinalBoneMatrices;
	}


	void PrintMatrix(const glm::mat4& matrix)//测试打印矩阵
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	void update() override {
		std::cout << "animator update\n";
	}

	//void Draw() override {
	//	std::cout << "animatorC Draw\n";
	//	if (m_CurrentAnimation) {
	//		std::cout << "animatorC rady\n";
	//		if (playing) {
	//			std::cout << "animatorC play\n";
	//			loadupdate();
	//		}
	//	}
	//}
	void loadupdate() {//灌入
		std::vector<glm::mat4> transforms = GetFinalBoneMatrices();
		for (int i = 0; i < transforms.size(); ++i) {
			shaderlist[0]->use();
			shaderlist[0]->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
			shaderlist[0]->setBool("play", true);
		}
	}
	void addanimation(animation _animation) {//加入动画到内部
		animationlist.push_back(new animation(_animation));
		m_CurrentAnimation = animationlist.back();
		PlayAnimation(m_CurrentAnimation);
	}

	std::vector<animation*> animationlist;
	std::vector<glm::mat4> m_FinalBoneMatrices;
	animation* m_CurrentAnimation;//播放动画
	float m_CurrentTime;//当前动画时间 
	float m_DeltaTime;
	bool playing = false;
};
std::vector<animator*> animatorlist;

