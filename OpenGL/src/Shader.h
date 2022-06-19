#pragma once
#include <string>
#include "GL/glew.h"
#include "mat4x4.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	

	std::unordered_map<std::string, int> m_UniformLocationCache;
public:

	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	GLuint CompileShader(GLuint type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader();
	/*
		Uniforms
	*/

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform4mat(const std::string& name, const glm::mat4& matrix);

private:
	int GetUniformLocation(const std::string& name);

};

