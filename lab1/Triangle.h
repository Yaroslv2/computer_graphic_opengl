#pragma once

#include <vector>
#include <array>

#include "Color.hpp"

class Triangle 
{
private:
	GLuint vbo;
	GLuint vao;
	GLuint shaderProgram;
	std::array<GLfloat, 9> points;
	Color color;

	GLfloat createVertexShader();
	GLfloat createFragmentShader();
public:
	Triangle(std::array<GLfloat, 9> points, Color);
	~Triangle();

	void draw();
};