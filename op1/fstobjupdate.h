#pragma once
#include "mounting.h"
#include "opengl_shader.h"

class fstobjupdate :
    public mounting
{
public:
	fstobjupdate() {};
	void update() override {

		//lihtflag = Input->getkey("k");
		//if (!lihtflag2 && lihtflag) {
		//	for (int i = 0; i < pt.size(); i++) {
		//		pt[i]->~Pthread();
		//	}
		//}
		//lihtflag2 = lihtflag;
		buttenflaglight = Input->getkey("m");
		if (!buttenflaglight2 && buttenflaglight) {
			Lightlist.addlight(light::Point, "lightpoint", glm::vec3(0.0f + Lightlist.LightVector.size() * 0.5, 2.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		}
		buttenflaglight2 = buttenflaglight;

		buttenflagmodelhe = Input->getkey("n");
		if (!buttenflagmodelhe2 && buttenflagmodelhe) {
			GameObject* obj = gameobjct;
			int num = 0;
			std::cout << std::endl;
			while (1) {
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
		}
		buttenflagmodelhe2 = buttenflagmodelhe;
	}
private:
	int processInput()
	{
		if (Input->getkey("esc")) {
			glfwSetWindowShouldClose(window->window, true);
			return 0;
		}
		return 0;
	}
	bool buttenflaglight = false;
	bool buttenflaglight2 = false;
	bool buttenflagmodelhe = false;
	bool buttenflagmodelhe2 = false;
	
};

