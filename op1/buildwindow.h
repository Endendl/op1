#pragma once
#ifndef BUILDWINDOW_H
#define BUILDWINDOW_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <Windows.h>
#include "init_tool.h"
#include "input.h"
#include "otime.h"
float deltaX, deltaY, lastX,lastY;//��������ƶ�
bool firstMosue = true;
GLsizei qwidth;
GLsizei qheight;
//float lastX = qwidth / 2, lastY = qheight / 2;//ȷ��������ĵ�
float inputmousex() {
	return deltaX;
}
float inputmousey() {
	return deltaY;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)//OpenGLע�ắ����û�δ��ڴ�С�仯����
{
	wwidth = width;
	wheight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {//OpenGLע�ắ���������궯��
	if (firstMosue)
	{
		lastX = xPos;
		lastY = yPos;
		firstMosue = false;
	}
	//std::cout << "���£�";
	Input->updatems(xPos, yPos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)//OpenGLע�ắ������������ֶ���
{
	Input->updateroll(xoffset, yoffset);
}
class buildwindow
{
public:
	buildwindow() {}
	buildwindow(GLsizei width, GLsizei height, const char* windowname, init_tool::os objos)
		:wwidth(width), wheight(height), windowsname(windowname), objos(objos)
	{

		window = glfwCreateWindow(wwidth, wheight, windowsname, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			//static_cast<wchar_t*> (objos);
		}
		glfwMakeContextCurrent(window);
		std::cout << "���ڹ����ɹ�" << std::endl;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//���ع�꣬����׽��
		//glfwSetInputMode(window, GLFW_CURSOR_NORMAL, GLFW_CURSOR_DISABLED);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		//glfwSetCursorPosCallback(window, mouse_callback);
		input = inputclass(window);//Ϊ���ڴ���һ��������
		qwidth = wwidth;
		qheight = wheight;
	}
	
public:
	GLFWwindow* window;//����
	init_tool::os objos;//ϵͳ���
	const char* windowsname;
	GLsizei wwidth;//�����
	GLsizei wheight;
	inputclass input;//����һ��������
};


#endif // !BUILDWINDOW_H


