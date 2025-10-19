#pragma once
#include<glm/glm.hpp>
#include<glfw3.h>


class Camera {
public:
	Camera();
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 value);
	void SetCameraDirection(glm::vec3 value);
	glm::vec3 GetLookAt();
	glm::vec3 GetUp();
	glm::vec3 GetCameraDirection();
	void MouseCallBack(GLFWwindow* window,float xpos, float ypos); //IE:handles all rotation as well as yaw
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	float cameraPitch;

private:
	glm::vec3 upVector;
	glm::vec3 lookAtVector;
	
	bool firstMouse;
	float cameralastX;
	float cameralastY;
	float cameraYaw;
};

