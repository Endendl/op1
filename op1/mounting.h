#pragma once
#ifndef MOUNTING_H
#define MOUNTING_H
#include "init_tool.h"
class GameObject;
class mounting
{
public:
	mounting() {};
	std::string name;
	virtual void update() {};//ʵ�ֹ��ظ���
	virtual void Draw() { std::cout << "0"; };
	GameObject* gameobjct;
	std::string tag = "?";
};

#endif // !MOUNTING_H
