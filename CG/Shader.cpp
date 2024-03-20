#include "Shader.h"
#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>

void Shader::Compile(const std::string filepath ) {
    auto source = ParseShader(filepath);
    std::cout << "Vertex shader:\n" << std::endl;
    std::cout << source.VertexSource << std::endl << std::endl;
    std::cout << "Fragment shader:\n" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int vs = CompileShader(source.VertexSource, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(source.FragmentSource, GL_FRAGMENT_SHADER);
    CompileProgram(vs, fs);
}

unsigned int Shader::CompileShader(std::string source, unsigned int shader_type)
{
    const char* source_code = source.c_str();
    unsigned int shaderID = glCreateShader(shader_type);

    glShaderSource(shaderID, 1, &source_code, NULL);
    glCompileShader(shaderID);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << (shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderID;
}

void Shader::CompileProgram(unsigned int vs, unsigned int fs){
    // link shaders to a program 
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shader after linking program because we dont need them 
    glDeleteShader(vs);
    glDeleteShader(fs);

    ID = shaderProgram;

}

ShaderProgramSource Shader::ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos) {

            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;//set mode to vertex
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;//set mode to fragment
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(),ss[1].str() };
}

int Shader::GetUniformLocation(const std::string& name){
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];


    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) 
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    else 
        m_UniformLocationCache[name] = location;

    return location;
}

void Shader::Bind(){
    glUseProgram(ID);
}

void Shader::Unbind(){
    glUseProgram(0);
}

void Shader::SetUniform1f(const std::string& name, const float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, const int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

