#pragma once
class otime
{
public:
	void update() {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	float getdeltaTime() {
		return deltaTime;
	}
	float getlastFrame() {
		return lastFrame;
	}
private:
	float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
	float lastFrame = 0.0f; // ��һ֡��ʱ��
};
otime optime;

