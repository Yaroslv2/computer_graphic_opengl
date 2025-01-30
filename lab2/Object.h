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
	void loadCoords(glm::vec3* verteces, size_t count);
	void loadColors(glm::vec3* colors, size_t count);
	void loadIndexes(GLuint* indices, size_t count);
	void loadShaders(const char* vect, const char* frag);
private:
	/// <summary>
	/// Vertex array object ID
	/// </summary>
	GLuint vaoID;
	size_t vertexCount = 0;
	size_t indexCount = 0;
	GLuint mode;
	/// <summary>
	/// Shader program ID
	/// </summary>
	GLuint shaderProgramID = -1;
};

