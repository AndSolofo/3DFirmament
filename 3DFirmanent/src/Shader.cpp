#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
    char* vertCode=readShader(vertexPath);
    char* fragCode=readShader(fragmentPath);

    unsigned int vertexShader, fragmentShader;
    //vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertCode, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
}

char* Shader::readShader(const char* filepath)
{
    
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open shader file: " << filepath << "\n";
        return nullptr;
    }

    // Get file size
    size_t fileSize = (size_t)file.tellg();
    if (fileSize == 0) {
        std::cerr << "ERROR: Shader file is empty: " << filepath << "\n";
        return nullptr;
    }

    // Allocate buffer (+1 for null terminator)
    char* buffer = new char[fileSize + 1];

    // Read file
    file.seekg(0);
    file.read(buffer, fileSize);
    buffer[fileSize] = '\0'; // Null-terminate

    // Verify we read everything
    if (file.gcount() != fileSize) {
        std::cerr << "ERROR: Failed to read complete shader file: " << filepath << "\n";
        delete[] buffer;
        return nullptr;
    }

    return buffer;
}

void Shader::SetMat4(const char* variable, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->programID, variable),1,GL_FALSE,glm::value_ptr(value));
}

void Shader::SetVec3(const char* variable, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(this->programID, variable),1,glm::value_ptr(value));
}

void Shader::SetFloat(const char* variable, float value)
{
    glUniform1f(glGetUniformLocation(this->programID,variable), value);
}

void Shader::SetInt(const char* variable, int value)
{
    glUniform1i(glGetUniformLocation(this->programID,variable), value);
}

void Shader::setBool(const char* variable, bool value)
{
    glUniform1i(glGetUniformLocation(this->programID,variable),value);
}

void Shader::use()
{
    glUseProgram(programID);
}
