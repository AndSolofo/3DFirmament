cmake_minimum_required(VERSION 3.15)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3DFirmament)

find_package(OpenGL REQUIRED)
target_link_libraries(3DFirmament PRIVATE OpenGL::GL)



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
)





