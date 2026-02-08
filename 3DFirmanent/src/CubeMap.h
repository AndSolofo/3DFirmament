#pragma once
#include<vector>
#include<string>
#include<glfw3.h>
#include<fstream>
#include "stb_image.h"
#include "RawVertices.h"
#include "Shader.h"
#include<iostream>
/*
* This Class serves as a SkyBok for our ligthing environment
*/
class CubeMap {
public:
	CubeMap();

	~CubeMap();

	void setUp(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);
	void Draw(Shader& shader);

private:
	unsigned int loadCubeMap(std::vector<std::string> faces);
	std::vector<std::string> m_Faces;
	unsigned int skyBoxVAO, skyBoxVBO;
	int m_textureID;
};
