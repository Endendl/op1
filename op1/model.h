#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"
#include "animdata.h"
#include "init_tool.h"
//#include "AnimatorController.h"
class AnimatorController;
class model :
	public GameObject
{
public:
	glm::vec3 Position;
	//AnimatorController* animatorController; // ָ�� AnimatorController �������ָ��//������ͳһ�Ľ�
	model(std::string _path) {
		transform.Position = glm::vec3(2, 2, 10);
		transform.rotate = glm::vec3(45.0f, 0, 0);
		transform.Scale = glm::vec3(1, 1.0f, 1);
		meshlist(this, _path);//����ģ��
		//mountingadd(new );
		//loadmodel(_path);
		std::string tmppath = _path;
		// �ҵ����һ����б�ܵ�λ��
		size_t lastSlashPos = tmppath.find_last_of("\\");
		// ��ȡ�ļ���
		name = tmppath.substr(0, (tmppath.find_last_of("."))).substr(lastSlashPos + 1);
		//PATH = PATH.substr(0, (PATH.find_last_of("\\")));
		//std::cout << name << std::endl;
	};
	~model() {};
	void update() override { 

	}
	void Draw(opengl_shader& shader) override {
		//std::cout <<  name << Drawmountinglist.size() << " :";
		for (int i = 0; i < Drawmountinglist.size(); i++)
		{
			Drawmountinglist[i]->Draw();
			//std::cout << Drawmountinglist[i]->name;
		}
	};
	auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }
private:
	std::map<std::string, BoneInfo> m_BoneInfoMap; //
	int m_BoneCounter = 0;
};
#endif
