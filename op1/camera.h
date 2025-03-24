#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "init_tool.h"
class camera :
	public GameObject
{
public:
	camera(glm::vec3  position, glm::vec3 target, glm::vec3 worldup) :
		Position(position),WorldUp(worldup) {
		this->name = "camera";
		//Position = position;
		//WorldUp = worldup;
		Forward = glm::normalize(target - position);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
		//Up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	camera(glm::vec3 Pos) : Position(Pos) {
		name = "camera";
		Forward = glm::normalize(Position - Target);//相机朝向
		Right = glm::normalize(glm::cross(WorldUp, Forward));//局部右轴 = 上向量叉乘朝向
		Up = glm::normalize(glm::cross(Forward, Right));//上轴
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	}

	camera(glm::vec3 Pos, float pitch, float yaw, float roll, glm::vec3 worldup) :Position(Pos), WorldUp(worldup) {
		name = "camera";
		Pitch = pitch;
		Yaw = yaw;
		Roll = roll;
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
	}
	bool lihtflag = false;
	bool lihtflag2 = false;
	void update() override {
		//float radius = 10.0f;//让相机绕着中心转的测试
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;//end
		//std::cout << "camer";
		gb(true);
		input();
		//lihtflag = Input->getkey("m");
		//if (!lihtflag2 && lihtflag) {
		//	Lightlist.addlight(light::Point, "lightpoint", glm::vec3(0.0f + Lightlist.LightVector.size() * 0.5, 2.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		//}
		//lihtflag2 = lihtflag;
		//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		updatecemeraview();
	};

	void updatecemeraview() {
		Forward = glm::vec3(0.0f, 0.0f, -1.0f);
		
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin( glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));//修正坐标系偏移；
		Forward = glm::normalize(front);
		
		//Forward = glm::normalize(front);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
		view = glm::lookAt(Position, Position + Forward, Up);//v矩阵
		//std::cout << "\nx" << Forward.x << "y" << Forward.y << "z" << Forward.z<<"p"<<Pitch<<"y"<<Yaw;
		projection = glm::perspective(glm::radians(fov), (float)wwidth / (float)wheight, 0.1f, 100.0f);//p矩阵
		//std::cout << "car" << Position.x;
	}

	void gb(bool on) {
		if (on) {
			glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	void input() {//输入有关
		
		//if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)

		if (fov >= 1.0f && fov <= 45.0f)
			fov -= Input->getaix("MouseRoll Y");
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;

		if (Input->getkey("up"))//改变窗口视角
		{
			fov++;
		}
		if (Input->getkey("down"))
		{
			fov--;
		}
		camrtime.update();
		float cameraSpeed = 2.5f * camrtime.getdeltaTime();
		//float cameraSpeed = 0.05f; // adjust accordingly
		if (Input->getkey("w"))
			Position += cameraSpeed * Forward;
		if (Input->getkey("s"))
			Position -= cameraSpeed * Forward;
		Yaw += Input->getaix("Mouse X") * optime.getdeltaTime() * 100;
		//std::cout << "\tcarx：" << Input->getaix("Mouse X");
		Pitch -= Input->getaix("Mouse Y") * optime.getdeltaTime() * 100;

		if (Input->getkey("a"))
			Position -= glm::normalize(glm::cross(Forward, Up)) * cameraSpeed;
		if (Input->getkey("d"))
			Position += glm::normalize(glm::cross(Forward, Up)) * cameraSpeed;
		if (Input->getkey("q"))
			Position += Up * cameraSpeed;
		if (Input->getkey("e"))
			Position -= Up * cameraSpeed;
		
		//std::cout << "m1 x :" << window->input.Mousex << std::endl;
		//std::cout << "m1 y :" << window->input.Mousey << std::endl;
		//std::cout << "m x :" << window->input.getaix("Mouse X") << std::endl;
		//std::cout << "m y :" << window->input.getaix("Mouse Y") << std::endl;
		
	}
	float fov = 45.0f;
	glm::vec3 Position;//位置
	glm::vec3 Target = glm::vec3(0.0f, 0.0f, 0.0f);//原点
	glm::vec3 Forward;//相机朝向
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);//世界上向量
	glm::vec3 Right;//局部右轴 = 上向量叉乘朝向
	glm::vec3 Up;//上轴
	glm::mat4 view;
	glm::mat4 projection;
	//void carmain() {
	//	maincar = this;
	//}
private:
	float Pitch = 0;
	float Yaw = 0;
	float Roll = 0;
	otime camrtime;

};
camera* maincar;
#endif // !CAMERA_H

