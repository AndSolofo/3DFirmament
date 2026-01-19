#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
public:
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void SetMat4(const char* varibale, glm::mat4 value);
	void SetVec3(const char* variable, glm::vec3 value);
	void SetFloat(const char* variable, float value);
	void SetInt(const char* variable,int value);
	void setBool(const char* variable, bool value);
	void use();
	unsigned int programID;
private:
	char* readShader(const char* filepath);

};
