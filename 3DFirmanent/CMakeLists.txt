cmake_minimum_required(VERSION 3.19)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3DFirmament)

find_package(OpenGL REQUIRED)
target_link_libraries(3DFirmament PRIVATE OpenGL::GL)


find_package(fmt CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE fmt::fmt)

find_package(glm CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE glfw3)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE imgui::imgui)

find_package(glad CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE glad::glad)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(3DFirmament PRIVATE assimp::assimp)

find_path(STB_INCLUDE_DIR "stb_image.h")
target_include_directories(3DFirmament PRIVATE ${STB_INCLUDE_DIR})



target_sources(3DFirmament
               PRIVATE  
               src/Application.cpp
               src/Camera.cpp
               src/CubeMap.cpp
               src/Frame_stats_menu.cpp
               src/LightingMenu.cpp
               src/main.cpp
               src/glad.c
               src/Mesh.cpp
               src/Model.cpp
               src/Shader.cpp
               src/stb_image_define.cpp
               
               PUBLIC FILE_SET HEADERS BASE_DIRS src FILES 
               src/Application.h
               src/Camera.h
               src/CubeMap.h
               src/Frame_stats_menu.h
               src/LightingMenu.h
               src/Model.h
               src/Shader.h
               src/Mesh.h

               PRIVATE
               src/shader/Fragment.shader
               src/shader/Lighting.shader
               src/shader/LightingVS.shader
               src/shader/Skybox.shader
               src/shader/SkyboxVS.shader
               src/shader/Vertex.shader
)





