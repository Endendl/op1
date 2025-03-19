#pragma once
#include <map>
#include <iostream>
class inputclass
{
public:
	inputclass() {};
	inputclass(GLFWwindow* _window) : getwindow(_window) {
		inputmap["a"] = GLFW_KEY_A;
		inputmap["b"] = GLFW_KEY_B;
		inputmap["c"] = GLFW_KEY_C;
		inputmap["d"] = GLFW_KEY_D;
		inputmap["e"] = GLFW_KEY_E;
		inputmap["f"] = GLFW_KEY_F;
		inputmap["g"] = GLFW_KEY_G;
		inputmap["h"] = GLFW_KEY_H;
		inputmap["i"] = GLFW_KEY_I;
		inputmap["j"] = GLFW_KEY_J;
		inputmap["k"] = GLFW_KEY_K;
		inputmap["l"] = GLFW_KEY_L;
		inputmap["m"] = GLFW_KEY_M;
		inputmap["n"] = GLFW_KEY_N;
		inputmap["o"] = GLFW_KEY_O;
		inputmap["p"] = GLFW_KEY_P;
		inputmap["q"] = GLFW_KEY_Q;
		inputmap["r"] = GLFW_KEY_R;
		inputmap["s"] = GLFW_KEY_S;
		inputmap["t"] = GLFW_KEY_T;
		inputmap["u"] = GLFW_KEY_U;
		inputmap["v"] = GLFW_KEY_V;
		inputmap["w"] = GLFW_KEY_W;
		inputmap["x"] = GLFW_KEY_X;
		inputmap["y"] = GLFW_KEY_Y;
		inputmap["z"] = GLFW_KEY_Z;
		inputmap["up"] = GLFW_KEY_UP;
		inputmap["down"] = GLFW_KEY_DOWN;
		inputmap["esc"] = GLFW_KEY_ESCAPE;
		
		
	};
	bool getkey(std::string keyname) {
		if (glfwGetKey(getwindow, inputmap[keyname]) == GLFW_PRESS) {
			return true;
		}
		return false;
	}

	float getaix(std::string aixname) {
			
		return inputfloats[aixname];//返还轴变量
		//return 0;
	}
	void updatend() {
		inputfloats["Mouse X"] = 0;
		inputfloats["Mouse Y"] = 0;
		inputfloats["MouseRoll X"] = 0;
		inputfloats["MouseRoll Y"] = 0;

	}
	void updateroll(double xPos, double yPos) {
		inputfloats["MouseRoll X"] = xPos;
		inputfloats["MouseRoll Y"] = yPos;
	}
	void updatems(double xPos, double yPos) {//改变帧数鼠标xy轴
		Mousex = xPos - lastX;//本帧数位置-上一帧位置
		Mousey = yPos - lastY;//本帧数位置-上一帧位置
		lastX = xPos;
		lastY = yPos;
		float sensitivity = 0.05f;
		inputfloats["Mouse X"] = Mousex * sensitivity;//让两个map指向对应的轴变量
		inputfloats["Mouse Y"] = Mousey * sensitivity;
		//std::cout << "\tinputx:" << inputfloats["Mouse X"];
	}
	float Mousex;
	float Mousey;
private:
	GLFWwindow* getwindow;
	std::map<std::string, int> inputmap;
	std::map<std::string, float> inputfloats;
	float lastX = wwidth / 2;//上一帧qwidth / 2, lastY = qheight / 2
	float lastY = wheight / 2;
	
};
inputclass* Input = NULL;;//主要输入指针