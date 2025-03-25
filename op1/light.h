#pragma once
#ifndef LIGHT_H
#define LIGHT_H	
class light :
	public GameObject//保存光源信息
{
public:
	light(int _mode, std::string _name,glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f)):
	position(_position), color(_color),name(_name)
	{
		name = "light";
		tag = "light";
		loadmod(_mode);
		//UpDatedirection();
	};
	light(int _mode, std::string _name,glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _angles = glm::vec3(0, 0, 0), glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f)) :
	position(_position), angles(glm::vec3(glm::radians(_angles.x), glm::radians(_angles.y), glm::radians(_angles.z))), color(_color), name(_name)
	{
		name = "light";
		tag = "light";
		loadmod(_mode);
		UpDatedirection();
	};
	std::string name;
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
	glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	float constant = 1.0f;
	float linear = 0.1f;
	float quadratic = 0.001f;
	float CosPhyInner = 0.9f;
	float CosPhyOutter = 0.85f;
	enum mode:int
	{
		Directional,
		Point,
		Spot,
		Ambient
	} mod;

	void update() {
		UpDatedirection();
	}

private:
	void UpDatedirection() {
		direction = glm::vec3(0, 0, 1.0f);//指向z
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
	}
	void loadmod(int _mode) {
		if (_mode == Directional) {
			mod = Directional;
		}
		else if (_mode == Point) {
			mod = Point;
		}
		else if (_mode == Spot)
		{
			mod = Spot;
		}
		else if (_mode == Ambient)
		{
			mod == Ambient;
		}
	}
};

class lightlist
{
public:
	std::vector<light> LightVector;
	void update() {

	}
	void addlight(int _mode, std::string _name, glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _angles = glm::vec3(0, 0, 0), glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f)) {
		std::string name = "light";
		LightVector.push_back(light(_mode, _name, _position, _angles, _color));
	}
	int LightNumber;
	int LightDirectionalNumber;
	int LightPoitNumber;
	int LightSpotNumber;
};
lightlist Lightlist;
#endif
