#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct PointLight {
    glm::vec3 position = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 intensity = glm::vec3(1.5f, 0.0f, 0.0f);
    float constant=1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    bool enabled = true;
};

struct DirectionalLight {
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 intensity = glm::vec3(0.3, 0.25, 0.2);
    bool enabled = true;
};

struct SpotLight {
    glm::vec3 position = glm::vec3(0.0f, 5.0f, 0.0f);
    glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 intensity = glm::vec3(1.0f, 1.0f, 1.0f); //AKA diffuse
    float innerCone = 12.5f;  // degrees
    float outerCone = 15.0f;  // degrees
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    bool enabled = true;
};

// Global light instances
PointLight pointLight;
DirectionalLight dirLight;
SpotLight spotLight;


class LightMenu {
public:
	LightMenu(GLFWwindow* window);
	~LightMenu();
	void Render();
};