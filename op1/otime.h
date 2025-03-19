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
	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间
};
otime optime;

