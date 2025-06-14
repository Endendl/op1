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
		tag = "notGameObject";
        //mountinglist.push_back(new fstobjupdate());
    };
    void update() override {
        //for (int i = 0; i < mountinglist.size(); i++) {
        //    mountinglist[i]->update();
        //}
		if (Input->getkey("u")) {
			setmousemode(0);
		}else
		if (Input->getkey("y")) {
			setmousemode(2);
		}
		
    }

    void Draw() override {
		if (Input->getkey("esc")) {
			glfwSetWindowShouldClose(window->window, true);
			return;
		}
		//processInput(window2->window);
		glfwMakeContextCurrent(window->window);//linshi
		//����ɫ
		
		glClearColor(Global_variables::Globalcolor.x, Global_variables::Globalcolor.y, Global_variables::Globalcolor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//GL_DEPTH_BUFFER_BIT�������Ȼ��� ɫ�� | ��Ȼ��� | ģ��
		glDepthFunc(GL_LESS);//��Ȼ�������
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF); // ����ģ�建��д��

		for (int i = 0; i < shaderlist.size(); i++)
		{
			shaderlist[i]->shaderload();
		}
		//imguistart();
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		//glfwPollEvents();
		//std::cout << "gui��ʼ��֡";
		
    }

};
firstobj stobj;//��һ�����壬��ʼ��ÿ֡