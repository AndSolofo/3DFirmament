#include "Application.h"

Application* Application::s_pResizeImpl = nullptr;
Application* Application::s_pCursorImpl = nullptr;

Application::Application() :m_Width(640),m_Height(480)
{
}

Application::~Application()
{

}

void Application::Run()
{
	if (!glfwInit()) {
		std::cerr << "ERROR:Failed to initialize OpenGl" << "\n";
		return;
	}
	//TODO:this is heavilly outdated and most likely won't run on other machines
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(m_Width, m_Height, "3DFirmament", NULL, NULL);
	if (!m_Window) {
		std::cerr << "ERROR::Failed to load window" << "\n";
		glfwTerminate(); 
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Camera);
	glfwSetFramebufferSizeCallback(m_Window, OnResize);
	glfwSetCursorPosCallback(m_Window, OnCursor);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "ERROR::Failed to initialize GLAD" << std::endl;
		return;
	}

	LightMenu lightMenu = LightMenu(m_Window);
	Shader shader = Shader("src/shader/Vertex.shader", "src/shader/Fragment.shader");
	Shader skyboxShader = Shader("src/shader/SkyboxVS.shader", "src/shader/Skybox.shader");
	m_Shader.push_back(shader);
	m_Shader.push_back(skyboxShader);
	bagModel = Model("src/Models/Gun_dae/Gun.dae");
	m_SkyBox.setUp("src/Skybox/skybox/right.jpg", "src/Skybox/skybox/left.jpg",
		           "src/Skybox/skybox/top.jpg", "src/Skybox/skybox/bottom.jpg",
		           "src/Skybox/skybox/front.jpg", "src/Skybox/skybox/back.jpg");
	
	while(!glfwWindowShouldClose(m_Window)){
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OnInput(m_Window);
		OnRender();
		//m_Shader[1] is Vertex and fragment shader of skybox
		m_SkyBox.Draw(m_Shader[1]);
		//m_Shader[0] indicates a standard Blinn-phong shader 
		bagModel.Draw(m_Shader[0]);
		lightMenu.Render();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void Application::OnRender()
{
	glEnable(GL_DEPTH_TEST);
	if (utilities.polygonMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glm::vec3 lightPosition = glm::vec3(1.5f, 2.0f, 1.5f);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(m_Camera.cameraPos, m_Camera.cameraPos + m_Camera.GetCameraDirection(), m_Camera.GetUp());
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), GetAspectRatio(m_Window), 0.1f, 100.0f);


	m_Shader[0].use();
	m_Shader[0].SetMat4("view", view);
	m_Shader[0].SetMat4("projection", projection);

	float lightX = sin(glfwGetTime() * 1.5f) * 5.0f;
	float lightZ = cos(glfwGetTime() * 1.5f) * 5.0f;
	lightPosition = glm::vec3(lightX, 5.0f, lightZ);  

	m_Shader[0].SetFloat("material.diffuse", 0.0f);
	m_Shader[0].SetFloat("material.specular", 1.0f);
	m_Shader[0].SetFloat("material.shininess", 1.0f);
	m_Shader[0].SetVec3("lightPos", lightPosition);
	m_Shader[0].SetVec3("viewPos", m_Camera.cameraPos);

	m_Shader[0].SetVec3("dirLights[0].position", glm::vec3(0.0f, -1.0f, 0.0f));
	m_Shader[0].SetVec3("dirLights[0].direction", dirLight.direction);
	m_Shader[0].SetVec3("dirLights[0].ambient", dirLight.color);
	m_Shader[0].SetVec3("dirLights[0].diffuse", dirLight.intensity);
	m_Shader[0].SetVec3("dirLights[0].specular", glm::vec3(0.5f, 0.5f, 0.5f));

	m_Shader[0].SetInt("numPointLights", 1);

	m_Shader[0].SetVec3("pointLights[0].position", pointLight.position);
	m_Shader[0].SetVec3("pointLights[0].diffuse", glm::vec3(1.5f, 0.0f, 0.0f));
	m_Shader[0].SetVec3("pointLights[0].specular", glm::vec3(1.0f));
	m_Shader[0].SetVec3("pointLights[0].ambient", pointLight.color);
	m_Shader[0].SetFloat("pointLights[0].constant", pointLight.constant);
	m_Shader[0].SetFloat("pointLights[0].linear", pointLight.linear);      // reduced from 0.09
	m_Shader[0].SetFloat("pointLights[0].quadratic", pointLight.quadratic);

	m_Shader[0].SetInt("numSpotLights", 1); // One spotlight

		// Spotlight 0
	m_Shader[0].SetVec3("spotLights[0].position", m_Camera.cameraPos);
	m_Shader[0].SetVec3("spotLights[0].direction", m_Camera.GetCameraDirection());
	m_Shader[0].SetFloat("spotLights[0].cutOff", glm::cos(glm::radians(spotLight.innerCone)));
	m_Shader[0].SetFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(spotLight.outerCone)));
	m_Shader[0].SetVec3("spotLights[0].ambient", spotLight.color);
	m_Shader[0].SetVec3("spotLights[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	m_Shader[0].SetVec3("spotLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	m_Shader[0].SetMat4("model", model);
	//set up for skybox shader
	
	m_Shader[1].use();
	glm::mat4 skyboxView = glm::mat4(glm::mat3(view));  //remove translation
	m_Shader[1].SetMat4("view", skyboxView);
	m_Shader[1].SetMat4("projection", projection);
	



}

void Application::OnResize(GLFWwindow* window, int width, int height)
{
	s_pResizeImpl= static_cast<Application*>(glfwGetWindowUserPointer(window));
	s_pResizeImpl->OnResizeImpl(window, width, height);
}

void Application::OnCursor(GLFWwindow* window, double xpos, double ypos)
{
	//TODO:are we deleting these pointers here
	s_pCursorImpl = static_cast<Application*>(glfwGetWindowUserPointer(window));
	s_pCursorImpl->OnCursorImpl(window, xpos, ypos);
}

void Application::OnResizeImpl(GLFWwindow* window, int width, int height)
{
	//TODO::fix viewport scaling issues
	glViewport(0, 0, width, height);

}

void Application::OnCursorImpl(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		Camera::MouseCallBack(window, (float)xpos, (float)ypos);
	}
}

void Application::OnInput(GLFWwindow* window)
{
	const  float cameraSpeed = 0.02f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Camera.cameraPos += cameraSpeed * m_Camera.GetCameraDirection();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_Camera.cameraPos -= cameraSpeed * m_Camera.GetCameraDirection();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_Camera.cameraPos += glm::normalize(glm::cross(m_Camera.GetCameraDirection(), m_Camera.GetUp())) * cameraSpeed;

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_Camera.cameraPos -= glm::normalize(glm::cross(m_Camera.GetCameraDirection(), m_Camera.GetUp())) * cameraSpeed;

	}
}

float Application::GetAspectRatio(GLFWwindow* window)
{
	int currentWidth, currentHeight;
	glfwGetWindowSize(window, &currentWidth, &currentHeight);
	return (float) currentWidth/(float) currentHeight;
}
