#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "mounting.h"
#include "opengl_shader.h"
class GameObject
{
public:
	opengl_shader* thisshader;
	GameObject() {
		transform.Position = glm::vec3(0, 0, 0);
		transform.Rotate = glm::vec3(45.0f, 0, 0);
		transform.Scale = glm::vec3(1, 1, 1);
	};
	struct
	{
		glm::vec3 Position;
		glm::vec3 Rotate;
		glm::vec3 Scale;

	}transform;

	void Pupdate() {//���ϸ�������
		update();
		updatemount();
		updateChildren();
	}

	void updatemount() {//�������й���
		for (int i = 0; i < mountinglist.size(); i++) {
			mountinglist[i]->update();
		}
	}
	void updateChildren() {
		for (int i = 0; i < Children.size(); i++) {
			Children[i]->Pupdate();
		}
	}
	virtual void update() {//�Զ�����·���

	}
	virtual void Draw() {//�Զ�����Ⱦ���� Darmmountinglist����mesh�Ͷ���������
		Draws();
		for (int i = 0; i < Drawmountinglist.size(); i++) {
			Drawmountinglist[i]->Draw();
		}
	}
	virtual void Draws() {};
	void mountingadd(mounting *_mounting) {
		mountinglist.push_back(_mounting);
		mountinglist.back()->gameobjct = this;
	}
	std::string name;
	std::vector<mounting*> mountinglist;
	std::vector<mounting*> Drawmountinglist;
	std::vector<GameObject*> Children;
	GameObject* nextOBJCT;
	std::string tag = "GameObject";
	glm::vec3 Forward;//�������
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);//����������
	glm::vec3 Right;//�ֲ����� = ��������˳���
	glm::vec3 Up;//����

private:
	
};
GameObject* OBJCT1;//
int objctNumber = 0;
int mountingadd(GameObject* obj, mounting* mounting) {
	if (obj == NULL) {
		return -1;
	}
	if (mounting == NULL)
	{
		return -2;
	}
	obj->mountingadd(mounting);
	return 0;
}

#endif // GAMEOBJCT_H


