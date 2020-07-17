#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "../utils/fileutils.h"

#include <glm/glm.hpp>;
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>

class Shader
{
private:
	GLuint m_RendererID;
	const std::string& m_VertPath;
	const std::string& m_FragPath;
	// This cache is used so that the glGetUniformLocation function does not have
	// to be called every single time. Performance improvement
	std::unordered_map <std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform1iv(const std::string& name, int count, int* v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
private:
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};