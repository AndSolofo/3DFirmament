#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
public:
	Shader();
<<<<<<< HEAD
	Shader(const char* vertexPath, const char* fragmentPath);
=======
>>>>>>> parent of 7b94561 (Final code commit)
	~Shader();
	char* readShader(const char* filepath);
	void SetMat4(const char* varibale, glm::mat4 value);
	void SetVec3(const char* variable, glm::vec3 value);
	void SetFloat(const char* variable, float value);
private:
	unsigned int programID;
};
