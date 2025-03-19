#pragma once
#ifndef OPENGLS_H
#define OPENGLS_H

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "buildwindow.h"
class opengls
{
public:
	opengls() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (objos == init_tool::mac) {
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		}
		wwidth = 800;
		wheight = 600;
		//buildwindow tp(wwidth,wheight,windowname,objos)
		window = new buildwindow(wwidth, wheight, windowname, objos);
		glfwMakeContextCurrent(window->window);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			//return;
		}
		
	}
public:
	buildwindow* window;
	const char* windowname = "opengl";
	init_tool::os objos;
	int wwidth;
	int wheight;
public:
	
};
opengls glmaster = opengls();
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


#endif // !OPENGLS_H


