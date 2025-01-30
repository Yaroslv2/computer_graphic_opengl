#pragma once

#include "libsInclude.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class Object
{
public:
	/// <summary>
	/// Простой конструктор - создаёт массив вершин, пока пустой.
	/// </summary>
	Object();
	~Object() {};
	void render();
	void setMode(GLuint mode);
	void setShaderProgram(GLuint shaderProgram);
	void setMatrixTransform(glm::mat4 matrix);
	void loadCoords(glm::vec3* verteces, size_t count);
	void loadColors(glm::vec3* colors, size_t count);
	void loadIndexes(GLuint* indices, size_t count);
	void loadShaders(const char* vect, const char* frag);
private:
	/// <summary>
	/// Vertex array object ID
	/// </summary>
	GLuint vaoID;
	size_t vertexCount;
	size_t indexCount;
	GLuint mode;
	/// <summary>
	/// Shader program ID
	/// </summary>
	GLuint shaderProgramID;
	glm::mat4 matrixTransform;
};

