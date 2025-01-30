#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath)
{
	std::string vertexShaderSource = loadFromFile(vertexShaderPath);
	std::string fragmentShaderSource = loadFromFile(fragmentShaderPath);

	id = create(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader()
{
	//glDeleteProgram(id);
}

void 
Shader::use()
{
	glUseProgram(id);
}

void Shader::setUniformMatrix4f(const std::string& name, glm::mat4& matrix)
{

	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

GLuint 
Shader::create(const std::string vertexShaderSource, const std::string fragmentShaderSource)
{
	GLuint program = glCreateProgram();

	GLuint vertexShader = compile(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "vertex_position");
	glBindAttribLocation(program, 1, "vertex_colour");

	glLinkProgram(program);

	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		char info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		
		std::cout << "CREATE SHADER PROGRAM ERROR: " << info << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

std::string 
Shader::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint 
Shader::compile(GLuint type, const std::string source)
{
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char info[512];
		glGetShaderInfoLog(shader, 512, nullptr, info);
		std::cout << "COMPILE SHADER ERROR: " << info << std::endl;
	}
	return shader;
}
