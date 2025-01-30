#pragma once

#include <vector>

#include "opengl_libs.h"

#include "Shader.h"

class Drawable
{
public:
	Drawable(GLuint mode, Shader shader);
	Drawable(Shader shader);
	/// <summary>
	/// Функция отрисовки
	/// </summary>
	void render();
	/// <summary>
	/// Установка 
	/// </summary>
	/// <param name="mode"></param>
	void setMode(GLuint mode);

	void setShader(Shader shader);
	void setMVPmatrix(glm::mat4 matrix);
	void setVertexes(glm::vec3* vertexes, size_t count);
	void setColors(glm::vec3* colors, size_t count);
	void setIndexes(GLuint* indexes, size_t count);
protected:
	void loadModelFromFile(const char* path);
	/// <summary>
	/// Вид отрисовки
	/// </summary>
	GLuint mode;
	/// <summary>
	/// "vertex array object ID", ID объекта, содержащего координаты и параметры
	/// всех вершин графического примитива
	/// </summary>
	GLuint vaoID;
	/// <summary>
	/// Шейдер
	/// </summary>
	Shader shader;
	/// <summary>
	/// Матрица преобразований
	/// </summary>
	glm::mat4 MVPmatrix;
	size_t indexesCount;
	size_t vertexCount;

	std::vector<glm::vec3> vertexes;
	std::vector<glm::vec2> texture;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
};

