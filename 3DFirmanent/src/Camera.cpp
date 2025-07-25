#include "Camera.h"

Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
	lookAtVector = glm::vec3(0.0f, 0.0f, 0.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    firstMouse = true;
    //TODO:fix magic numbers
    cameraYaw = 0;
    cameraPitch = 0;
    cameralastX = 0.0f;
    cameralastY = 0.0f;
}


glm::vec3 Camera::GetPosition()
{
	return cameraPos;
}

void Camera::SetPosition(glm::vec3 value)
{
	cameraPos = value;
}

void Camera::SetCameraDirection(glm::vec3 value)
{
	cameraDirection = value;
}

glm::vec3 Camera::GetLookAt()
{
	return lookAtVector;
}

glm::vec3 Camera::GetUp()
{
	return upVector;
}

glm::vec3 Camera::GetCameraDirection()
{
	return cameraDirection;
}

void Camera::MouseCallBack(GLFWwindow* window,float xpos,float ypos)
{
    const float mouseSensitivity = 0.5f;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    if (firstMouse) {
        cameralastX = (float)width / 2;;
        cameralastY = (float)height/2;
        firstMouse = false;
    }
    float xOffset = xpos - cameralastX;
    float yOffset = ypos - cameralastY;
    cameralastX = xpos;
    cameralastY = ypos;


    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    cameraYaw += xOffset;
    cameraPitch += yOffset;

    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    glm::vec3 cameraDirection;
    cameraDirection.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    cameraDirection.y = -sin(glm::radians(cameraPitch));
    cameraDirection.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    SetCameraDirection(glm::normalize(cameraDirection));
    
}



