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
float deltaX, deltaY, lastX,lastY;//捕获鼠标移动
bool firstMosue = true;
GLsizei qwidth;
GLsizei qheight;
//float lastX = qwidth / 2, lastY = qheight / 2;//确定鼠标中心点
float inputmousex() {
	return deltaX;
}
float inputmousey() {
	return deltaY;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)//OpenGL注册函数，没次窗口大小变化调用
{
	wwidth = width;
	wheight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {//OpenGL注册函数，监控鼠标动向
	if (firstMosue)
	{
		lastX = xPos;
		lastY = yPos;
		firstMosue = false;
	}
	//std::cout << "更新：";
	Input->updatems(xPos, yPos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)//OpenGL注册函数，监控鼠标滚轮动向
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
		std::cout << "窗口构建成功" << std::endl;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏光标，并捕捉它
		//glfwSetInputMode(window, GLFW_CURSOR_NORMAL, GLFW_CURSOR_DISABLED);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		//glfwSetCursorPosCallback(window, mouse_callback);
		input = inputclass(window);//为窗口创建一个输入检测
		qwidth = wwidth;
		qheight = wheight;
	}
	
public:
	GLFWwindow* window;//窗体
	init_tool::os objos;//系统检测
	const char* windowsname;
	GLsizei wwidth;//长宽高
	GLsizei wheight;
	inputclass input;//创建一个输入检测
};


#endif // !BUILDWINDOW_H


