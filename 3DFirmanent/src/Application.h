#pragma once
#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include<string>
#include<vector>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Frame_stats_menu.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"
#include "LightingMenu.h"
#include "CubeMap.h"



class Application {
public:
	Application();

	~Application();

	void Run();

	void OnRender();

	float GetAspectRatio(GLFWwindow* window);

	static void OnResize(GLFWwindow* window, int width, int height);

	static void OnCursor(GLFWwindow* window, double xpos, double ypos);
private:
	void OnResizeImpl(GLFWwindow* window, int width, int height);
	void OnCursorImpl(GLFWwindow* window, double xpos, double ypos);
	void OnInput(GLFWwindow* window);
	int m_Width=640;
	int m_Height=480;
	const unsigned int MAX_SHADER = 2;

	GLFWwindow* m_Window=nullptr;
	Camera m_Camera;
	std::vector<Shader> m_Shader;
	Model bagModel;
	CubeMap m_SkyBox;
	//static variables in order to access OpenGL resize callbacks
	static Application* s_pResizeImpl;
	static Application* s_pCursorImpl;


};
