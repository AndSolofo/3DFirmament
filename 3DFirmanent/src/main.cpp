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




const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;


void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);


//Global variables
Camera mainCamera;

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    


    /* Create a windowed mode window and its OpenGL context */

    GLFWwindow* window= glfwCreateWindow(WIDTH, HEIGHT, "3DFirmament", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallback);
    glfwSetCursorPosCallback(window,cursor_position_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //stbi_set_flip_vertically_on_load(true);
    LightMenu lightMenu(window);

    
    //FIXME:make it relative linking
    Shader cubeShader("C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/Vertex.shader","C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/Fragment.shader");

    cubeShader.use(); 
    cubeShader.SetInt("material.diffuse", 0);  // Texture unit 0
    cubeShader.SetInt("material.specular", 1); // Texture unit 1
   

    glm::vec3 lightPosition = glm::vec3(1.5f, 2.0f, 1.5f);
     
    Model bagModel("C:/3DFirmament/3DFirmanent/3DFirmanent/src/Models/backpack.obj");
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    
    while (!glfwWindowShouldClose(window))
    {
        // Process input and clear buffers
        processInput(window);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        // Set up view/projection matrices
        glm::mat4 view = glm::lookAt(mainCamera.cameraPos,
            mainCamera.cameraPos + mainCamera.GetCameraDirection(),
            mainCamera.GetUp());
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            640.0f / 480.0f, 0.1f, 100.0f);


        // Activate shader and set matrices
        cubeShader.use();
        cubeShader.SetMat4("view", view);
        cubeShader.SetMat4("projection", projection);

        // View position
        cubeShader.SetVec3("viewPos", mainCamera.cameraPos);

        // ========== DIRECTIONAL LIGHT ==========
        cubeShader.SetVec3("dirLights[0].position", glm::vec3(0.0f, -1.0f, 0.0f));
        cubeShader.SetVec3("dirLights[0].direction", dirLight.direction);
        cubeShader.SetVec3("dirLights[0].ambient", dirLight.color);
        cubeShader.SetVec3("dirLights[0].diffuse", dirLight.intensity);
        cubeShader.SetVec3("dirLights[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));

        // ========== POINT LIGHT ==========
        cubeShader.SetInt("numPointLights", 1);

        cubeShader.SetVec3("pointLights[0].position", pointLight.position);
        cubeShader.SetVec3("pointLights[0].diffuse", glm::vec3(1.5f, 0.0f, 0.0f));
        cubeShader.SetVec3("pointLights[0].specular", glm::vec3(1.0f));
        cubeShader.SetVec3("pointLights[0].ambient", pointLight.color);
        cubeShader.SetFloat("pointLights[0].constant", pointLight.constant);
        cubeShader.SetFloat("pointLights[0].linear", pointLight.linear);      // reduced from 0.09
        cubeShader.SetFloat("pointLights[0].quadratic", pointLight.quadratic);

        


        cubeShader.SetInt("numSpotLights", 1); // One spotlight

        // Spotlight 0
        cubeShader.SetVec3("spotLights[0].position", mainCamera.cameraPos);
        cubeShader.SetVec3("spotLights[0].direction", mainCamera.GetCameraDirection());
        cubeShader.SetFloat("spotLights[0].cutOff", glm::cos(glm::radians(spotLight.innerCone)));
        cubeShader.SetFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(spotLight.outerCone)));
        cubeShader.SetVec3("spotLights[0].ambient", spotLight.color);
        cubeShader.SetVec3("spotLights[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        cubeShader.SetVec3("spotLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.2f));	
        
        cubeShader.SetMat4("model", model);

        bagModel.Draw(cubeShader);
        lightMenu.Render();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();


    return 0;
}


void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        mainCamera.MouseCallBack(window, (float)xpos, (float)ypos);
    }
    

}

void processInput(GLFWwindow* window)
{
    const  float cameraSpeed = 0.02f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mainCamera.cameraPos += cameraSpeed * mainCamera.GetCameraDirection();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mainCamera.cameraPos -= cameraSpeed * mainCamera.GetCameraDirection();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mainCamera.cameraPos += glm::normalize(glm::cross(mainCamera.GetCameraDirection(), mainCamera.GetUp())) * cameraSpeed;
        
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mainCamera.cameraPos -= glm::normalize(glm::cross(mainCamera.GetCameraDirection(), mainCamera.GetUp())) * cameraSpeed;
        
    }
}








