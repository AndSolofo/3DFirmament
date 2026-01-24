#pragma once
<<<<<<< HEAD
#include "Application.h"


int main(void)
{
    try {
        Application app;
        app.Run();
        return 0;
    }
    catch (std::exception& exc) {
        std::cerr <<"ERROR::RUNNING APP: " << exc.what() << "\n";
        return -1;
    }
=======
#include<glad/glad.h>
#include<glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>
#include<string>
#include<vector>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Frame_stats_menu.h"
#include "Shader.h"


const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;


void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
//TODO:fix the file path not everyone has it in this directory

//Global variables
Camera mainCamera;
Frame_Stats_Menu frameDataMenu;
Shader shaderClass;

const char* vertexShaderCode = shaderClass.readShader("C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/Vertex.shader");

const char* fragmentShaderCode = shaderClass.readShader("C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/Fragment.shader");

const char* lightingShaderCode = shaderClass.readShader("C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/Lighting.shader");

const char* lightingShaderVSCode = shaderClass.readShader("C:/3DFirmament/3DFirmanent/3DFirmanent/src/shader/LIghtingVS.shader");



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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallback);
    glfwSetCursorPosCallback(window,cursor_position_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    unsigned int indices[] = {
        // Front face (vertices 0,1,2,3)
        0, 1, 2,  2, 3, 0,
        // Back face (vertices 4,5,6,7)
        4, 5, 6,  6, 7, 4,
        // Left face (vertices 7,3,0,4)
        7, 3, 0,  0, 4, 7,
        // Right face (vertices 1,5,6,2)
        1, 5, 6,  6, 2, 1,
        // Bottom face (vertices 0,1,5,4)
        0, 1, 5,  5, 4, 0,
        // Top face (vertices 3,2,6,7)
        3, 2, 6,  6, 7, 3
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,1);
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader =glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int shaderPorgram;
    shaderPorgram = glCreateProgram();
    glAttachShader(shaderPorgram, vertexShader);
    glAttachShader(shaderPorgram, fragmentShader);
    glLinkProgram(shaderPorgram);
    glGetProgramiv(shaderPorgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderPorgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINKING::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    unsigned int lightingShaderVS;
    lightingShaderVS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lightingShaderVS, 1, &lightingShaderVSCode, NULL);
    glCompileShader(lightingShaderVS);
    if (!success) {
        glGetShaderInfoLog(lightingShaderVS, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LIGHTINGVS::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int lightingShader;
    lightingShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lightingShader, 1, &lightingShaderCode, NULL);
    glCompileShader(lightingShader);
    glGetShaderiv(lightingShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(lightingShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LIGHTING::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int lightingProgram;
    lightingProgram = glCreateProgram();
    glAttachShader(lightingProgram, lightingShaderVS);
    glAttachShader(lightingProgram, lightingShader);
    glLinkProgram(lightingProgram);
    glGetProgramiv(lightingProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(lightingProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::LIGHTINGSHADER::LINKING::COMPILATION FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(lightingShader);
    glDeleteShader(lightingShaderVS);

    

    //Vertex attributes-->layout(location=0)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    


    //EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    
    //texture using stb_image

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data0 = stbi_load("container2.jpg", &width, &height, &nrChannels, 0);
    if (data0)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    unsigned char* data1 = stbi_load("specular.jpg", &width, &height, &nrChannels, 0);
    if (data1) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data0);
    stbi_image_free(data1);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    glUseProgram(shaderPorgram);
    glUniform1f(glGetUniformLocation(shaderPorgram, "material.diffuse"), 0.0f);
    glUniform1f(glGetUniformLocation(shaderPorgram, "material.specular"), 1.0f);
   
    

    
    //lighting VAO
    glUseProgram(lightingProgram);
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //light cube positions
    glm::vec3 lightCubePosition[] = {
        glm::vec3(0.0f,3.0f,10.0f),
        glm::vec3(3.0f,10.0f,3.0f),
        glm::vec3(8.0f,3.0f,1.0f)
    };
    //textured cube postions
    glm::vec3 textureCubePosition[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 lightPosition = (textureCubePosition[0] + textureCubePosition[1] + textureCubePosition[2]) / 3.0f;

    // Move the light slightly above and behind for better illumination
    


    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(mainCamera.cameraPos, mainCamera.cameraPos + mainCamera.GetCameraDirection(), mainCamera.GetUp());
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
        int viewLoc = glGetUniformLocation(shaderPorgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shaderPorgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glUseProgram(shaderPorgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        float lightX = sin(glfwGetTime() * 1.5f) * 5.0f;
        float lightZ = cos(glfwGetTime() * 1.5f) * 5.0f;
        lightPosition = glm::vec3(lightX, 5.0f, lightZ);  // Y position fixed at 5.
        glUseProgram(shaderPorgram);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUniform3f(glGetUniformLocation(shaderPorgram, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
        glUniform3f(glGetUniformLocation(shaderPorgram, "viewPos"), mainCamera.cameraPos.x,mainCamera.cameraPos.y,mainCamera.cameraPos.z);
        glUniform1f(glGetUniformLocation(shaderPorgram, "material.diffuse"), 0.0f);  // Texture unit 0
        glUniform1f(glGetUniformLocation(shaderPorgram, "material.specular"), 1.0f); // Texture unit 1
        glUniform1f(glGetUniformLocation(shaderPorgram, "material.shininess"), 32.0f);
        /*glUniform3f(glGetUniformLocation(shaderPorgram, "light.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(shaderPorgram, "light.diffuse"), 0.9f, 0.8f, 0.6f);
        glUniform3f(glGetUniformLocation(shaderPorgram, "light.specular"), 1.0f, 1.0f, 0.9f);
        glUniform3f(glGetUniformLocation(shaderPorgram, "light.direction"), -0.2f, -1.0f, -0.3f);
        glUniform1f(glGetUniformLocation(shaderPorgram, "light.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shaderPorgram, "light.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(shaderPorgram, "light.quadratic"), 0.032f);
        */
        // Spotlight position (camera position)
        glUniform3f(glGetUniformLocation(shaderPorgram, "spotLight.position"),
            mainCamera.cameraPos.x,
            mainCamera.cameraPos.y,
            mainCamera.cameraPos.z);

        // Spotlight direction (camera forward)
        glUniform3f(glGetUniformLocation(shaderPorgram, "spotLight.direction"),
            mainCamera.GetCameraDirection().x,
            mainCamera.GetCameraDirection().y,
            mainCamera.GetCameraDirection().z);

        // SUPER WIDE angle (45 degrees instead of 30)
        glUniform1f(glGetUniformLocation(shaderPorgram, "spotLight.cutOff"),
            glm::cos(glm::radians(45.0f)));

        // BRIGHT ambient light (white)
        glUniform3f(glGetUniformLocation(shaderPorgram, "spotLight.ambient"),
            0.8f, 0.8f, 0.8f);

        // NEON RED diffuse (very intense)
        glUniform3f(glGetUniformLocation(shaderPorgram, "spotLight.diffuse"),
            2.0f, 0.2f, 0.2f);

        // SUPER BRIGHT white specular
        glUniform3f(glGetUniformLocation(shaderPorgram, "spotLight.specular"),
            3.0f, 3.0f, 3.0f);

        // Attenuation - almost no falloff
        glUniform1f(glGetUniformLocation(shaderPorgram, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shaderPorgram, "spotLight.linearVal"), 0.007f);  // Very small
        glUniform1f(glGetUniformLocation(shaderPorgram, "spotLight.quadratic"), 0.0002f); // Tiny

        
        

        
        for (int i = 0; i < 10; i++) {
            float angle = 40.0f;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, textureCubePosition[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));  // Fixed rotation axis

            int modelLoc = glGetUniformLocation(shaderPorgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /*
        glUseProgram(lightingProgram);
        int projLocLighting = glGetUniformLocation(lightingProgram, "projection");
        int viewLocLighting = glGetUniformLocation(lightingProgram, "view");

        // Set the projection and view matrices
        glUniformMatrix4fv(projLocLighting, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLocLighting, 1, GL_FALSE, glm::value_ptr(view));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,lightPosition );
        model = glm::scale(model, glm::vec3(0.2f));
        int lightingLoc = glGetUniformLocation(lightingProgram, "model");
        glUniformMatrix4fv(lightingLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        */
        

        //glClear(GL_COLOR_BUFFER_BIT);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        //processInput(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();


    return 0;
}


void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mainCamera.MouseCallBack(window,(float)xpos, (float)ypos);

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
>>>>>>> parent of 7b94561 (Final code commit)
}






<<<<<<< HEAD





=======
>>>>>>> parent of 7b94561 (Final code commit)
