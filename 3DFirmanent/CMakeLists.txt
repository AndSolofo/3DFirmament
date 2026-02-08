cmake_minimum_required(VERSION 3.15)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(3DFirmament)

target_sources(3DFirmament
               PRIVATE 
               # Source files
               src/Application.cpp
               src/Camera.cpp
               src/CubeMap.cpp
               src/Frame_stats_menu.cpp
               src/LightingMenu.cpp
               src/main.cpp
               src/Mesh.cpp
               src/Model.cpp
               src/Shader.cpp
               src/stb_image_define.cpp
               
               # Header files
               src/Application.h
               src/Camera.h
               src/CubeMap.h
               src/Frame_stats_menu.h
               src/LightingMenu.h
               src/Model.h
               src/Shader.h
               src/Mesh.h
               
               # Shader files
               src/shader/Fragment.shader
               src/shader/Lighting.shader
               src/shader/LightingVS.shader
               src/shader/Skybox.shader
               src/shader/SkyboxVS.shader
               src/shader/Vertex.shader
)

