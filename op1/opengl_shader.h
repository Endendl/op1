#pragma once
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "init_tool.h"

class opengl_shader
{
public:
	opengl_shader() {};
	opengl_shader(std::string _name, const char* vertexPath, const char* fragmentPath) :
		name(_name) {
		in1t(vertexPath, fragmentPath);
	};
	void in1t(const char* vertexPath, const char* fragmentPath){
		vertPath = vertexPath;
		fragPath = fragmentPath;
		//����shader�ļ�
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ��֤ifstream��������׳��쳣��
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// ���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			if (!vShaderFile.is_open() || !fShaderFile.is_open())
			{
				throw std::exception("open file error");
			}
			std::stringstream vShaderStream, fShaderStream;
			// ��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// �ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();
			// ת����������string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (const std::exception& ex)
		{
			std::cout << "shaderԴ��ת���쳣" << ex.what();
		}
		//Դ�������
		const char* vertexSource;
		const char* fragmentSource;
		vertexSource = vertexCode.c_str();
		fragmentSource = fragmentCode.c_str();
		//std::cout << "vs\n" << vertexSource << "\nfs\n" << fragmentSource;
		//����shader
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);;//��ɫ����Ӧ��ID����ɫ����Ӧ��ID��
		//���ص���ɫ���е�Դ���룬Ϊconst GLchar **����//�ַ������ȵ����飬Ϊconst GLint *����
		glCompileShader(vertex);//����
		shaderdebugerr(vertex, "vertex:");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		shaderdebugerr(fragment, "fragment:");
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		shaderdebugerr(ID, "shader:");
		GLint successs;
		glGetProgramiv(ID, GL_LINK_STATUS, &successs);
		if (!successs) {
			GLchar infoLog[512];
			glGetProgramInfoLog(ID, 512, nullptr, infoLog);
			std::cerr << "Shader program linking failed: " << infoLog << std::endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
		//if (!this->compileAndLink()) {
		//	std::cerr << "Shader compilation/linking failed!" << std::endl;
		//	// ��ӡ������־
		//	std::cerr << shader->getErrorLog() << std::endl;
		//}
	}
public:
	unsigned int ID;
	std::string name;
	enum slot
	{
		DIFFUSE,
		SPECULAR
	};
	std::string vertPath;
	std::string fragPath;
public:
	void update() {
		use();
		shaderload();
	}

	void use() {
		//std::cout << "bind id = " << ID << std::endl;
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, int value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	//void setMat4(const std::string& name, const glm::mat4& mat) const
	//{
	//	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	//}
	void shaderdebugerr(int id, const char* errstr) {
		int success;
		char infoLog[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			std::cout << errstr << "������" << infoLog << std::endl;
		};
	}
	virtual void shaderload() {};//��ͬshader��ͬд������shader�������

	int rendering() {
		return 0;
	}
};
std::vector<opengl_shader*> shaderlist;
void shaderlistdel() {
	for (int i = 0; i < shaderlist.size(); i++)
	{
		glDeleteProgram(shaderlist[i]->ID);
	}
	
}
#endif // !OPENGL_SHADER_H

#include "shader.h"


