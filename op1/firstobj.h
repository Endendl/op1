#pragma once
#include "GameObject.h"
#include "mounting.h"
#include "fstobjupdate.h"
class firstobj :
    public GameObject
{
public:
    firstobj() {
		name = "firstobj";
        //mountinglist.push_back(new fstobjupdate());
    };
    void update() override {
        //for (int i = 0; i < mountinglist.size(); i++) {
        //    mountinglist[i]->update();
        //}
		
    }

    void Draw() override {
		if (Input->getkey("esc")) {
			glfwSetWindowShouldClose(window->window, true);
			return;
		}
		//processInput(window2->window);
		glfwMakeContextCurrent(window->window);//linshi
		//����ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//GL_DEPTH_BUFFER_BIT�������Ȼ��� ɫ�� | ��Ȼ��� | ģ��
		glDepthFunc(GL_LESS);//��Ȼ�������
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF); // ����ģ�建��д��

		for (int i = 0; i < shaderlist.size(); i++)
		{
			shaderlist[i]->shaderload();
		}

		
    }

};
firstobj stobj;//��һ�����壬��ʼ��ÿ֡