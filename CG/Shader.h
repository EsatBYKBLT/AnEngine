#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	unsigned int ID{}; 
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;


	unsigned int CompileShader(std::string source, unsigned int shader_type);
	void CompileProgram(unsigned int vs, unsigned int fs);

	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);

public:
	void Compile();
	void Bind();
	void Unbind();


	void SetUniform1f(const std::string& name, const float value);
	void SetUniform1i(const std::string& name, const int value);
	void setUniformMat4f(const std::string& name, const glm::mat4& mat);


};

