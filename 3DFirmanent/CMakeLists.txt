cmake_minimum_required(VERSION 3.15)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)

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
               src/Application.cxx
               src/Camera.cxx
               src/CubeMap.cxx
               src/Frame_stats_menu.cxx
               src/Lighting_menu.cxx
               src/main.cxx
               src/Mesh.cxx
               src/Model.cxx
               src/Shader.cxx
               src/stb_image_define.cxx)

target_include_directories(3DFirmament PRIVATE src)

target_link_libraries(3DFirmament 
    PRIVATE 
        OpenGL::GL
        glfw
        assimp::assimp
        glm::glm
        imgui
)



