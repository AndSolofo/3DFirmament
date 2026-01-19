#include "Shader.h"

Shader::Shader()
<<<<<<< HEAD
{
}

Shader::Shader(const char* vertexPath,const char* fragmentPath)
=======
>>>>>>> parent of 7b94561 (Final code commit)
{
}

Shader::~Shader()
{
}

char* Shader::readShader(const char* filepath)
{
    
    std::ifstream file(filepath);
    std::string content;
    std::stringstream buffer;
    if (!file.is_open()) {
        std::cerr << "Unable to open file";
    }
    buffer << file.rdbuf();
    file.close();
    content = buffer.str();
    char* result = new char[content.size() + 1];
    std::memcpy(result, content.c_str(), content.size() + 1);

    return result;
}

void Shader::SetMat4(const char* varibale, glm::mat4 value)
{
}

void Shader::SetVec3(const char* variable, glm::vec3 value)
{
}

void Shader::SetFloat(const char* variable, float value)
{
}
