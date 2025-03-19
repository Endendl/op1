#pragma once
#ifndef INIT_TOOL
#define INIT_TOOL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <memory>
#include <semaphore>
#include <iostream>
#include <map>

#include <vector>
#include "optime.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assimp_glm_helpers.h"
#include <thread>
std::string PATH;
namespace init_tool {
	enum os {
		windows, linux_red, linux_debian, linux_arch, mac, ios
	};
}
init_tool::os objos;
class initinfo
{
public:
	initinfo() {};
	const int getPthreadNUM() {
		return PthreadNUM;
	}
	~initinfo() {};
	int PthreadNUM = 4;

private:

};
initinfo in1tinfo;

#endif // !INIT_TOOL
