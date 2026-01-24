#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    
    char* vShaderCode = readShader(vertexPath);
    char* fShaderCode = readShader(fragmentPath);

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    
    
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertex);
    glAttachShader(this->programID, fragment);
    glLinkProgram(this->programID);
    
    
    glGetProgramiv(this->ID, GL_LINK_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    
    delete[] vShaderCode;
    delete[] fShaderCode;
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

void Shader::use(){
    glUseProgram(thsi->programID)
}

void Shader::SetMat4(const char* variable, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, variable), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const char* variable, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(this->ID, variable), value.x, value.y, value.z);
}

void Shader::SetFloat(const char* variable, float value)
{
    glUniform1f(glGetUniformLocation(this->ID, variable), value);
}