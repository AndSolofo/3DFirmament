cmake_minimum_required(VERSION 3.15)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD ON)

find_package(OpenGL REQUIRED)
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")
set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/dependencies/glfw3.lib")
set(ASSIMP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")
set(ASSIMP_LIBRARY "${CMAKE_SOURCE_DIR}/Dependencies/assimp.lib")  # Adjust filename as needed
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")

add_library(imgui STATIC
    Dependencies/ImGui/imgui.cpp
    Dependencies/ImGui/imgui_demo.cpp
    Dependencies/ImGui/imgui_draw.cpp
    Dependencies/ImGui/imgui_tables.cpp
    Dependencies/ImGui/imgui_widgets.cpp
    Dependencies/ImGui/backends/imgui_impl_glfw.cpp
    Dependencies/ImGui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC 
    Dependencies/ImGui
    Dependencies/ImGui/backends
)

add_executable(3DFirmament)


target_sources(3DFirmament
               PRIVATE 
               src/Application.cpp
               src/Camera.cpp
               src/CubeMap.cpp
               src/Frame_stats_menu.cpp
               src/LightingMenu.cpp
               src/main.cpp
               src/Mesh.cpp
               src/Model.cpp
               src/Shader.cpp
               src/stb_image_define.cpp)

target_include_directories(3DFirmament PRIVATE src)

target_link_libraries(3DFirmament 
    PRIVATE 
        OpenGL::GL
        glfw
        assimp::assimp
        glm::glm
        imgui
)



