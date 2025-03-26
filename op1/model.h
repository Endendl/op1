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
	//AnimatorController* animatorController; // 指向 AnimatorController 派生类的指针//挂载类统一改进
	model(std::string _path) {
		tag = "model";
		transform.Position = glm::vec3(2, 2, 10);
		transform.rotate = glm::vec3(45.0f, 0, 0);
		transform.Scale = glm::vec3(1, 1.0f, 1);
		meshlist tmpmesh(this, _path);//一次性工具类meshlist内封装了众多构造所需函数，减少mesh占用资源，会把mesh提取出来加到模型物体的两个挂载队列下
		m_BoneInfoMap = tmpmesh.m_BoneInfoMap;
		m_BoneCounter = tmpmesh.m_BoneCounter;
		//std::cout<< " model " << GetBoneCount();
		//meshlist(this, _path);//载入模型
		//mountingadd(new );
		//loadmodel(_path);
		std::string tmppath = _path;
		// 找到最后一个反斜杠的位置
		size_t lastSlashPos = tmppath.find_last_of("\\");
		// 提取文件名
		name = tmppath.substr(0, (tmppath.find_last_of("."))).substr(lastSlashPos + 1);
		//PATH = PATH.substr(0, (PATH.find_last_of("\\")));
		//std::cout << name << std::endl;
	};
	~model() {};
	void update() override { 

	}
	void Draw() override {
		//std::cout <<  name << Drawmountinglist.size() << " :";
		for (int i = 0; i < Drawmountinglist.size(); i++)
		{
			Drawmountinglist[i]->Draw();
			//std::cout << Drawmountinglist[i]->name;
		}
		thisshader->setBool("play", false);
	};
	auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }
private:
	std::map<std::string, BoneInfo> m_BoneInfoMap; //
	int m_BoneCounter = 0;
};
#endif
