#pragma once
#ifndef OPENGLX_H
#define OPENGLX_H
#define STB_IMAGE_IMPLEMENTATION
#include <memory>
#include <vector>
#include <iostream>
#include <stb_image.h>
int wwidth;
int wheight;
#include "buildwindow.h"
#include "input.h"
#include "opengl_shader.h"
//#include "IncludeMount.h"
//#include "IncludeGameobjct.h"
#include "GameObject.h"
using std::shared_ptr;
using std::make_shared;

#include "light.h"

#include "camera.h"

#include "shader_lige.h"
#include "shader_litcube.h"
#include "shader_a.h"

#include "Material.h"
#include "mesh.h"
#include "model.h"
#include "animation.h"
#include "animator.h"
#include "animatorC.h"

#include "AnimatorController.h"
#include "testAnimatorController.h"
#include "LinkNode.h"
#include "firstobj.h"

#include "Pthread.h"

#include "collision.h"
#include "SphereCollision.h"
#include "CapsuleCollision.h"
#include "CubeCollision.h"
#include "imgui_ui.h"
#include "ui_GameObjct_list.h"
#include "ui_objmounts_list.h"
#include "ui_Global_variables.h"

#include "Json_lode.h"
//#include "imgui_ui.h"
//#include "ImGui/imgui.h"
//buildwindow* window2;
const char* windowname = "opengl";
const char* windowname2 = "opengl2";

//firstobj stobj();
int processInput(GLFWwindow* window)
{
	if (Input->getkey("esc")) {
		glfwSetWindowShouldClose(window, true);
		return 0;
	}
	return 0;
}
void openginit() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (objos == init_tool::mac) {
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}
	wwidth = 1920;
	wheight = 1080;
	const char* windownames = std::string("OpenGL" + std::to_string(wwidth) + "*" + std::to_string(wheight)).c_str();
	std::cout << windownames<<"������";
	//buildwindow tp(wwidth,wheight,windowname,objos)
	window = new buildwindow(wwidth, wheight, windownames, objos);

	//window2 = new buildwindow(wwidth, wheight, windowname2, objos);
	glfwMakeContextCurrent(window->window);
	//glfwSwapInterval(1); // ���ô�ֱͬ��
	//glfwMakeContextCurrent(window2->window);

	//glfwSetFramebufferSizeCallback(window2->window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	Input = &(window->input);
	glEnable(GL_DEPTH_TEST);//��Ȼ��忪��
	glEnable(GL_STENCIL_TEST);//ģ����Կ���

#pragma region imgui init

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();//��ɫ����
	ImGui_ImplGlfw_InitForOpenGL(window->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

};
GameObject* thisis;


model* objss;
animator* animast;
void in1tjson() {
	objp = new fp(stobj);
	OBJCT1 = &stobj;
	stobj.nextOBJCT = linknode;
	if (linknode) {
		linknode->backDOBJECT = &stobj;
	}
}
void in1tdemo() {
	//��ɫ�����
	shaderlist.push_back(new shader_a("a", std::string(PATH + "\\assets\\shader\\a3.vert").c_str(), std::string(PATH + "\\assets\\shader\\a.frag").c_str()));
	shaderlist.push_back(new shader_lige("lite", std::string(PATH + "\\assets\\shader\\litevs.vert").c_str(), std::string(PATH + "\\assets\\shader\\litefs.frag").c_str()));
	shaderlist.push_back(new shader_litcube("litcube", std::string(PATH + "\\assets\\shader\\litcube00.vert").c_str(), std::string(PATH + "\\assets\\shader\\litcube00.frag").c_str()));
	//����������
	objp = new fp(stobj);
	OBJCT1 = &stobj;
	stobj.nextOBJCT = linknode;
	if (linknode) {
		linknode->backDOBJECT = &stobj;
	}
	stobj.mountingadd(new fstobjupdate());
	//DObjctadd(new camera(glm::vec3(0.0f, 0.0f, -3.0f), 0.0f, 90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	//DObjctadd(new imgui_ui());
	DObjctadd(new ui_GameObjct_list());
	DObjctadd(new ui_objmounts_list());
	DObjctadd(new ui_Global_variables());
	DObjctadd(new camera(glm::vec3(0.0f, 0.0f, -3.0f), 0.0f, 90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	maincar = static_cast<camera*>(linknode->backDOBJECT);
	DObjctadd(new model(PATH + "\\assets\\model\\backpack\\backpack.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[0];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);
	
	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\liandao.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[0];

	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\liandao.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[0];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);
	
	thisis = linknode->backDOBJECT;
	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\nanosuit.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[0];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);

	DObjctadd(new model(PATH + "\\assets\\model\\45\\45.dae"));
	std::string path = PATH + "\\assets\\model\\45\\45.dae";
	linknode->backDOBJECT->thisshader = shaderlist[0];
	linknode->backDOBJECT->transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	linknode->backDOBJECT->transform.Rotate = glm::vec3(0.0f, 0.0f, 0.0f);
	linknode->backDOBJECT->transform.Scale = glm::vec3(0.020f, 0.020f, 0.020f);

	objss = dynamic_cast<model*>(linknode->backDOBJECT);
	//std::cout <<" obj " << objss->GetBoneCount();
	animationslist.push_back(animation(path, objss));//���붯����������
	animatorlist.push_back(new animatorC());
	animast = animatorlist.back();
	animast->gameobjct = objss;
	animast->addanimation(animationslist.back());
	addtestAnimatorController(objss, new testAnimatorCcontroller(animast));//���������������Ͷ�����
	
	//std::cout << "name" << animationslist.back().name;

	//shader

	Lightlist.addlight(light::Directional, "lightdir", glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Lightlist.addlight(light::Spot, "lights", glm::vec3(0.0f, 2.0f, 1.0f), glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));



	if (PthreadStart) {
		for (int i = 0; i < 4; ++i) {
			pt.push_back(std::make_unique<Pthread>(i));
		}
	}


}
bool lihtflag = false;
bool lihtflag2 = false;
void in1t() {//��ʼ��
	//bool in1ton = true;
	while (1) {//������ʼ������
		imguistart();
		glfwMakeContextCurrent(window->window);//linshi
		//����ɫ
		glClearColor(Global_variables::Globalcolor.x, Global_variables::Globalcolor.y, Global_variables::Globalcolor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//GL_DEPTH_BUFFER_BIT�������Ȼ��� ɫ�� | ��Ȼ��� | ģ��
		glDepthFunc(GL_LESS);//��Ȼ�������
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF); // ����ģ�建��д��

		static char text[512] = "n"; // ���������㹻��

		if (ImGui::InputText("path", text, IM_ARRAYSIZE(text))) {
		}
		if (ImGui::Button("json lodeing")) {
			Json_lode lodejson;
			std::string load(text);
			lodejson.openjson(load);
			glfwSwapBuffers(window->window);
			glfwPollEvents();
			in1tjson();
			break;
		}
		if (ImGui::Button("in1t demo")) {
			imguiend();
			glfwSwapBuffers(window->window);
			glfwPollEvents();
			in1tdemo();
			break;
		}
		imguiend();
		glfwSwapBuffers(window->window);
		glfwPollEvents();
		
	}
	
}

void runupdate(){//���߳�

	GameObject* obj = &stobj;
	int num = 0;
	std::cout << std::endl;
	//while (1) {
	//	std::cout << "��ţ�" << num << " �������ƣ�" << obj->name << std::endl;
	//	std::cout << "���������-" << " ������" << obj->Children.size() << "{" << std::endl;
	//	for (int i = 0; i < obj->Children.size(); i++)
	//	{
	//		std::cout << i << ":" << obj->Children[i]->name << "  " << std::endl;
	//	}
	//	std::cout << "}\n���ض���-" << " ������" << obj->mountinglist.size() << "{" << std::endl;
	//	for (int i = 0; i < obj->mountinglist.size(); i++)
	//	{
	//		std::cout << i << ":" << obj->mountinglist[i]->name << "  " << std::endl;
	//	}
	//	std::cout << "}\n�ɻ��ƹ��ض���-" << " ������" << obj->Drawmountinglist.size() << "{" << std::endl;
	//	for (int i = 0; i < obj->Drawmountinglist.size(); i++)
	//	{
	//		std::cout << i << ":" << obj->Drawmountinglist[i]->name << "  " << std::endl;
	//	}
	//	std::cout << "}" << std::endl;
	//	num++;
	//	if (obj->nextOBJCT == NULL)
	//	{
	//		break;
	//	}
	//	obj = obj->nextOBJCT;
	//}
	std::cout << std::endl;
	std::cout << std::endl;

	while (!glfwWindowShouldClose(window->window))
	{
		
		optime.update();
		while (objp->mode) {
			OBJCT1 = objp->getobj();
			OBJCT1->Pupdate();
		}
		// �ȴ��������߳����һ��ѭ��
		//if (Pends >= m) {
			//Input->updatend();//ֹͣ����

			sem_main_acquire();
			imguistart();
			/*ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();*/

			// ���ƶ���
			while (objp->mode == 0) {
				OBJCT1 = objp->getobj();
				OBJCT1->Draw();
				//std::cout << OBJCT1->name;
				//std::cout << "1";
				
			}
			//ImGui::End();

			Pends = 0;
			objp->mode = 1;
			Input->updatend();

			imguiend();

			//ImGui::Render();    // imgui ����֡
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window->window);
			glfwPollEvents();
			sem_thread_release();
			
		//}
	
	}
}
int rend() {
	in1t();
	//in1tdemo();
	bool lihtflag = false;
	bool lihtflag2 = false;
	//Pthread ba(1);
	//�������߳�
	

	runupdate();
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	shaderlistdel();
	glfwTerminate();
	return 0;
}


#endif // !OPENGLX_H

