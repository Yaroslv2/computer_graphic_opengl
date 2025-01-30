#pragma once

#include "libsInclude.h"
#include <map>
#include <string>

class ShadersManager
{
public:
	static ShadersManager& getInstanse();
	void init();
	GLuint createShaderProgram(const char* vs, const char* fs, std::string name);
	bool contains(std::string name);
	GLuint getShaderProgram(std::string name);
	void setShaderProgram(GLuint shaderProgramID, std::string name);
private:
	std::string loadShader(const char* filename);
	ShadersManager();
	static ShadersManager instanse;

	std::map <std::string, GLuint> shaders;
};

