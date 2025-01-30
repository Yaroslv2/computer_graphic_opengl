#pragma once

#include <string>

#include "opengl_libs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
	~Shader();

	void use();
	void setUniformMatrix4f(const std::string& name, glm::mat4& matrix);
private:
	GLuint id;
	
	GLuint create(const std::string vertexShaderSource, const std::string fragmentShaderSource);
	std::string loadFromFile(const std::string& filename);
	GLuint compile(GLuint type, const std::string source);
};
