#include "Triangle.h"

GLfloat 
Triangle::createVertexShader()
{
	const char* vertexShaderString =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
	glCompileShader(vertexShader);

	return vertexShader;
}

GLfloat 
Triangle::createFragmentShader()
{
	std::string fragmentShaderString = 
		"#version 400\n"
		"out vec4 frag_colour;\n"
		"void main()\n"
		"{\n"
		"frag_colour = vec4("+ color.toString() + ");\n"
		"}";
	const char* fss = fragmentShaderString.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);

	return fragmentShader;
}

Triangle::Triangle(std::array<GLfloat, 9> points, Color color)
	: color(color),
	  points(points),
	  vbo(0),
	  vao(0)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLfloat fragmentShader = createFragmentShader();
	GLfloat vertexShader = createVertexShader();

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
}

Triangle::~Triangle()
{
}

void 
Triangle::draw()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
