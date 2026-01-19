#include "LightingMenu.h"





LightMenu::LightMenu(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();  
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

LightMenu::~LightMenu()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void LightMenu::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	
    if (ImGui::Begin("Light Controls"))
    {
        if (ImGui::CollapsingHeader("Useful Utilities")) {
            //by default the model runs without polygon mode
            if (ImGui::Checkbox("Polygon Mode", &utilities.polygonMode)) {
            }

            if(ImGui::Checkbox("Depth Mode",&utilities.depthMode)){}
        }
        // Point Light Section
        if (ImGui::CollapsingHeader("Point Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Checkbox("Enable##PointLight", &pointLight.enabled);

            if (pointLight.enabled)
            {
                ImGui::Separator();

                // Position
                ImGui::Text("Position");
                ImGui::SliderFloat3("##PointPos", &pointLight.position.x, -10.0f, 10.0f);

                // Color
                ImGui::Text("Color");
                ImGui::ColorEdit3("##PointColor", &pointLight.color.x);

                // Intensity
                ImGui::Text("Intensity");
                ImGui::SliderFloat3("##PointIntensity", &pointLight.intensity.x, 0.0f, 5.0f);

                // Attenuation
                ImGui::Text("Attenuation");
                ImGui::SliderFloat("Constant##Point", &pointLight.constant, 0.1f, 2.0f);
                ImGui::SliderFloat("Linear##Point", &pointLight.linear, 0.001f, 0.3f);
                ImGui::SliderFloat("Quadratic##Point", &pointLight.quadratic, 0.0001f, 0.1f);

                // Quick presets
                ImGui::Text("Distance Presets:");
                ImGui::SameLine();
                if (ImGui::Button("7##Point")) {
                    pointLight.constant = 1.0f;
                    pointLight.linear = 0.7f;
                    pointLight.quadratic = 1.8f;
                }
                ImGui::SameLine();
                if (ImGui::Button("13##Point")) {
                    pointLight.constant = 1.0f;
                    pointLight.linear = 0.35f;
                    pointLight.quadratic = 0.44f;
                }
                ImGui::SameLine();
                if (ImGui::Button("20##Point")) {
                    pointLight.constant = 1.0f;
                    pointLight.linear = 0.22f;
                    pointLight.quadratic = 0.20f;
                }
                ImGui::SameLine();
                if (ImGui::Button("32##Point")) {
                    pointLight.constant = 1.0f;
                    pointLight.linear = 0.14f;
                    pointLight.quadratic = 0.07f;
                }
                ImGui::SameLine();
                if (ImGui::Button("50##Point")) {
                    pointLight.constant = 1.0f;
                    pointLight.linear = 0.09f;
                    pointLight.quadratic = 0.032f;
                }
            }
            else {
                pointLight.color= glm::vec3(0.0f, 0.0f, 0.0f);
                pointLight.intensity = glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }

        ImGui::Spacing();

        // Directional Light Section
        if (ImGui::CollapsingHeader("Directional Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Checkbox("Enable##DirLight", &dirLight.enabled);

            if (dirLight.enabled)
            {
                ImGui::Separator();

                // Direction
                ImGui::Text("Direction");
                ImGui::SliderFloat3("##DirDirection", &dirLight.direction.x, -1.0f, 1.0f);

                // Normalize button
                ImGui::SameLine();
                if (ImGui::Button("Normalize##Dir"))
                {
                    dirLight.direction = glm::normalize(dirLight.direction);
                }

                // Color
                ImGui::Text("Color");
                ImGui::ColorEdit3("##DirColor", &dirLight.color.x);

                // Intensity
                ImGui::Text("Intensity");
                ImGui::SliderFloat3("##DirIntensity", &dirLight.intensity.x, 0.0f, 2.0f);

                // Direction presets
                ImGui::Text("Direction Presets:");
                if (ImGui::Button("Sun High")) {
                    dirLight.direction = glm::vec3(0.0f, -1.0f, 0.0f);
                }
                ImGui::SameLine();
                if (ImGui::Button("Sun Low")) {
                    dirLight.direction = glm::vec3(0.3f, -0.8f, 0.2f);
                }
                ImGui::SameLine();
                if (ImGui::Button("Sunset")) {
                    dirLight.direction = glm::vec3(0.8f, -0.3f, 0.2f);
                }
            }
            else {
                dirLight.color = glm::vec3(0.0f, 0.0f, 0.0f);
                dirLight.intensity = glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }

        ImGui::Spacing();

        // Spot Light Section
        if (ImGui::CollapsingHeader("Spot Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Checkbox("Enable##SpotLight", &spotLight.enabled);

            if (spotLight.enabled)
            {
                ImGui::Separator();

                // Direction
                ImGui::Text("Direction");
                ImGui::SliderFloat3("##SpotDirection", &spotLight.direction.x, -1.0f, 1.0f);

                // Normalize button
                ImGui::SameLine();
                if (ImGui::Button("Normalize##Spot"))
                {
                    spotLight.direction = glm::normalize(spotLight.direction);
                }

                // Color
                ImGui::Text("Color");
                ImGui::ColorEdit3("##SpotColor", &spotLight.color.x);

                // Intensity
                ImGui::Text("Intensity");
                ImGui::SliderFloat3("##SpotIntensity", &spotLight.intensity.x, 0.0f, 5.0f);

                // Cone angles
                ImGui::Text("Cone Angles (degrees)");
                ImGui::SliderFloat("Inner Cone", &spotLight.innerCone, 1.0f, 89.0f);
                ImGui::SliderFloat("Outer Cone", &spotLight.outerCone, 1.0f, 90.0f);

                // Ensure inner cone is always <= outer cone
                if (spotLight.innerCone > spotLight.outerCone)
                {
                    spotLight.outerCone = spotLight.innerCone;
                }

                // Attenuation
                ImGui::Text("Attenuation");
                ImGui::SliderFloat("Constant##Spot", &spotLight.constant, 0.1f, 2.0f);
                ImGui::SliderFloat("Linear##Spot", &spotLight.linear, 0.001f, 0.3f);
                ImGui::SliderFloat("Quadratic##Spot", &spotLight.quadratic, 0.0001f, 0.1f);

                // Quick presets
                ImGui::Text("Distance Presets:");
                ImGui::SameLine();
                if (ImGui::Button("7##Spot")) {
                    spotLight.constant = 1.0f;
                    spotLight.linear = 0.7f;
                    spotLight.quadratic = 1.8f;
                }
                ImGui::SameLine();
                if (ImGui::Button("13##Spot")) {
                    spotLight.constant = 1.0f;
                    spotLight.linear = 0.35f;
                    spotLight.quadratic = 0.44f;
                }
                ImGui::SameLine();
                if (ImGui::Button("20##Spot")) {
                    spotLight.constant = 1.0f;
                    spotLight.linear = 0.22f;
                    spotLight.quadratic = 0.20f;
                }
                ImGui::SameLine();
                if (ImGui::Button("32##Spot")) {
                    spotLight.constant = 1.0f;
                    spotLight.linear = 0.14f;
                    spotLight.quadratic = 0.07f;
                }
                ImGui::SameLine();
                if (ImGui::Button("50##Spot")) {
                    spotLight.constant = 1.0f;
                    spotLight.linear = 0.09f;
                    spotLight.quadratic = 0.032f;
                }

                // Cone presets
                ImGui::Text("Cone Presets:");
                if (ImGui::Button("Narrow")) {
                    spotLight.innerCone = 5.0f;
                    spotLight.outerCone = 7.5f;
                }
                ImGui::SameLine();
                if (ImGui::Button("Medium")) {
                    spotLight.innerCone = 12.5f;
                    spotLight.outerCone = 15.0f;
                }
                ImGui::SameLine();
                if (ImGui::Button("Wide")) {
                    spotLight.innerCone = 25.0f;
                    spotLight.outerCone = 30.0f;
                }
                ImGui::SameLine();
                if (ImGui::Button("Flashlight")) {
                    spotLight.innerCone = 8.0f;
                    spotLight.outerCone = 12.0f;
                }
            }
            else {
                spotLight.color = glm::vec3(0.0f, 0.0f, 0.0f);
                spotLight.intensity = glm::vec3(0.0f,0.0f,0.0f);
            }
        }

        ImGui::Spacing();
        ImGui::Separator();

        // Global controls
        if (ImGui::Button("Reset All Lights"))
        {
            pointLight = PointLight();
            dirLight = DirectionalLight();
            spotLight = SpotLight();
        }

        ImGui::SameLine();
        if (ImGui::Button("Disable All"))
        {
            pointLight.enabled = false;
            dirLight.enabled = false;
            spotLight.enabled = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Enable All"))
        {
            pointLight.enabled = true;
            dirLight.enabled = true;
            spotLight.enabled = true;

        }
    }
    ImGui::End();

	// Render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
