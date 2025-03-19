#pragma once
class Material
{
public:
	Material(opengl_shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) :
		shader(_shader),ambient(_ambient),diffuse(_diffuse),specular(_specular), shininess(_shininess){
	}
	Material(opengl_shader* _shader, glm::vec3 _ambient, unsigned int _texdiffuse, glm::vec3 _specular, float _shininess) :
		shader(_shader),ambient(_ambient),texdiffuse(_texdiffuse),specular(_specular), shininess(_shininess){
	}
	Material(opengl_shader* _shader, glm::vec3 _ambient, unsigned int _texdiffuse, unsigned int _texspecular, float _shininess) :
		shader(_shader),ambient(_ambient),texdiffuse(_texdiffuse), texspecular(_texspecular), shininess(_shininess){
	}
	opengl_shader* shader;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	unsigned int texdiffuse;
	unsigned int texspecular;
	glm::vec3 specular;
	float shininess;
	//Ë¥¼õ
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

};

