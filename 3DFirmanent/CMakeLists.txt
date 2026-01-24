cmake_minimum_required(VERSION 3.15)
project(3DFirmament VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")
set(GLFW_LIBRARY "${CMAKE_SOURCE_DIR}/Dependencies/glfw3.lib")
set(ASSIMP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")
set(ASSIMP_LIBRARY "${CMAKE_SOURCE_DIR}/Dependencies/assimp.lib")
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
    ${GLFW_INCLUDE_DIR}
)

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
               
               # Shader files
               src/shader/Fragment.shader
               src/shader/Lighting.shader
               src/shader/LightingVS.shader
               src/shader/Skybox.shader
               src/shader/SkyboxVS.shader
               src/shader/Vertex.shader
)

target_include_directories(3DFirmament PRIVATE 
    src
    ${GLFW_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
)

target_link_libraries(3DFirmament 
    PRIVATE 
        OpenGL::GL
        ${GLFW_LIBRARY}
        ${ASSIMP_LIBRARY}
        imgui
)

# Copy shader files to build directory after build
add_custom_command(TARGET 3DFirmament POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/shader
    $<TARGET_FILE_DIR:3DFirmament>/shader
    COMMENT "Copying shaders to build directory"
)