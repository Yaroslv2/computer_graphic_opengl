#pragma once
#include "GLUtils.h"
class Shader
{
private:
	GLuint shaderId = -1;
public:
	Shader();
	~Shader();

	void Use();
	void UniformMatrix(std::string name, Matrix4x4 matrix);
	void Load(std::string vertexPath, std::string fragmentPath);
};

