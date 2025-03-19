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
buildwindow* window;
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

#include "ImGui/imgui.h"
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
	std::cout << windownames<<"窗口名";
	//buildwindow tp(wwidth,wheight,windowname,objos)
	window = new buildwindow(wwidth, wheight, windownames, objos);

	//window2 = new buildwindow(wwidth, wheight, windowname2, objos);
	glfwMakeContextCurrent(window->window);
	//glfwMakeContextCurrent(window2->window);

	//glfwSetFramebufferSizeCallback(window2->window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	Input = &(window->input);
	glEnable(GL_DEPTH_TEST);//深度缓冲开启
	glEnable(GL_STENCIL_TEST);//模板测试开启
};
GameObject* thisis;
void in1t() {
	//着色器添加
	shaderlist.push_back(new shader_a("a", std::string(PATH + "\\assets\\shader\\a.vert").c_str(), std::string(PATH + "\\assets\\shader\\a.frag").c_str()));
	shaderlist.push_back(new shader_lige("lite", std::string(PATH + "\\assets\\shader\\litevs.vert").c_str(), std::string(PATH + "\\assets\\shader\\litefs.frag").c_str()));
	shaderlist.push_back(new shader_litcube("litcube", std::string(PATH + "\\assets\\shader\\litcube00.vert").c_str(), std::string(PATH + "\\assets\\shader\\litcube00.frag").c_str()));
	//物体存活链表
	objp = new fp(stobj);
	OBJCT1 = &stobj;
	stobj.nextOBJCT = linknode;
	if (linknode) {
		linknode->backDOBJECT = &stobj;
	}
	stobj.mountingadd(new fstobjupdate());
	DObjctadd(new camera(glm::vec3(0.0f, 0.0f, -3.0f), 0.0f, 90.0f, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	maincar = static_cast<camera*>(linknode->backDOBJECT);
	DObjctadd(new model(PATH + "\\assets\\model\\backpack\\backpack.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[1];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);

	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\liandao.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[1];
	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\liandao.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[1];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);

	thisis = linknode->backDOBJECT;
	DObjctadd(new model(PATH + "\\assets\\model\\nanosuit\\nanosuit.obj"));
	linknode->backDOBJECT->thisshader = shaderlist[1];
	add_SphereCollision(linknode->backDOBJECT, 0, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);


	DObjctadd(new model(PATH + "\\assets\\model\\45\\45.dae"));
	std::string path = PATH + "\\assets\\model\\45\\45.dae";
	linknode->backDOBJECT->thisshader = shaderlist[0];
	linknode->backDOBJECT->transform.Position = glm::vec3(10.0f, -6.0f, 0.0f);
	linknode->backDOBJECT->transform.rotate = glm::vec3(0.0f, 0.0f, 0.0f);
	linknode->backDOBJECT->transform.Scale = glm::vec3(0.05f, 0.05f, 0.05f);

	model* objss = dynamic_cast<model*>(linknode->backDOBJECT);
	//animationslist.push_back(animation(path, objss));//加入动画进动画机
	//addtestAnimatorController(objss, new testAnimatorCcontroller());//创建动画控制器和动画机
	//animator* animorss= dynamic_cast<animator*>(objss->Drawmountinglist[0]);//获取动画机
	//animorss->addanimation(animationslist[0]);//动画机插入动画

	if(objss->Drawmountinglist[0] == NULL)
	std::cout << "objss->Drawmountinglist[0]->name";
	//std::cout << objss->Drawmountinglist[0]->name;
	
	//dynamic_cast<testAnimatorCcontroller*>(objss->Drawmountinglist[0])->addanimator(objss, );
	
	//linknode->backDOBJECT->thisshader = shaderlist[0];

	//shader
	

	Lightlist.addlight(light::Directional, "lightdir", glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	Lightlist.addlight(light::Spot, "lights", glm::vec3(0.0f, 2.0f, 1.0f), glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}
bool lihtflag = false;
bool lihtflag2 = false;


void runupdate(){//主线程

	GameObject* obj = &stobj;
	int num = 0;
	std::cout << std::endl;
	while (0) {
		std::cout << "编号：" << num << " 物体名称：" << obj->name << std::endl;
		std::cout << "子物体队列-" << " 数量：" << obj->Children.size() << "{" << std::endl;
		for (int i = 0; i < obj->Children.size(); i++)
		{
			std::cout << i << ":" << obj->Children[i]->name << "  " << std::endl;
		}
		std::cout << "}\n挂载队列-" << " 数量：" << obj->mountinglist.size() << "{" << std::endl;
		for (int i = 0; i < obj->mountinglist.size(); i++)
		{
			std::cout << i << ":" << obj->mountinglist[i]->name << "  " << std::endl;
		}
		std::cout << "}\n可绘制挂载队列-" << " 数量：" << obj->Drawmountinglist.size() << "{" << std::endl;
		for (int i = 0; i < obj->Drawmountinglist.size(); i++)
		{
			std::cout << i << ":" << obj->Drawmountinglist[i]->name << "  " << std::endl;
		}
		std::cout << "}" << std::endl;
		num++;
		if (obj->nextOBJCT == NULL)
		{
			break;
		}
		obj = obj->nextOBJCT;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	while (!glfwWindowShouldClose(window->window))
	{
		while (objp->mode) {
			OBJCT1 = objp->getobj();
			OBJCT1->Pupdate();
		}
		// 等待所有子线程完成一次循环
		if (Pends >= m) {
			//Input->updatend();//停止更新

			for (int i = 0; i < m; i++) {
				sem_main.acquire();
			}
			// 绘制对象
			while (objp->mode == 0) {
				OBJCT1 = objp->getobj();
				OBJCT1->Draw(*shaderlist[0]);
				//std::cout << "1";
				
			}
			Pends = 0;
			objp->mode = 1;
			Input->updatend();


			glfwSwapBuffers(window->window);
			glfwPollEvents();
			for (int i = 0; i < m; ++i) {
				sem_thread.release();
			}
			
		}
	
	}
}
int rend() {
	in1t();
	bool lihtflag = false;
	bool lihtflag2 = false;
	//Pthread ba(1);
	//创建子线程
	for (int i = 0; i < 4; ++i) {
		pt.push_back(std::make_unique<Pthread>(i));
	}


	runupdate();

	//for (int i = 0; i < pt.size(); i++) {
	//	pt[i].reset(); // 销毁线程对象
	//}
	//pt.clear();
	//for (size_t i = 0; i < pt.size(); i++)
	//{
	//	pt[i]->~Pthread();
	//}
	
	shaderlistdel();
	glfwTerminate();
	return 0;
}


#endif // !OPENGLX_H

