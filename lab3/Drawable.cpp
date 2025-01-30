#include "Drawable.h"

Drawable::Drawable(GLuint mode, Shader shader)
	: mode(mode),
	vaoID(0),
	shader(shader),
	MVPmatrix(glm::mat4(1.0f)),
	indexesCount(0),
	vertexCount(0)
{
	/// Создание массива вершин, и запись его ID в переданный параметр
	glGenVertexArrays(1, &vaoID);
}

Drawable::Drawable(Shader shader)
	: mode(GL_TRIANGLES),
	vaoID(0),
	shader(shader),
	MVPmatrix(glm::mat4(1.0f)),
	indexesCount(0),
	vertexCount(0)
{
	/// Создание массива вершин, и запись его ID в переданный параметр
	glGenVertexArrays(1, &vaoID);
}

void 
Drawable::render()
{
	shader.use();

	shader.setUniformMatrix4f("MVP", MVPmatrix);

	glBindVertexArray(vaoID);

	if (indexesCount > 0)
		glDrawElements(mode, indexesCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, vertexCount);
}

void 
Drawable::setMode(GLuint mode)
{
	this->mode = mode;
}

void 
Drawable::setShader(Shader shader)
{
	this->shader = shader;
}

void 
Drawable::setMVPmatrix(glm::mat4 matrix)
{
	MVPmatrix = matrix;
}

void 
Drawable::setVertexes(glm::vec3* vertexes, size_t count)
{
	vertexCount = count;

	GLuint vertexes_vbo;
	glGenBuffers(1, &vertexes_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertexes_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), vertexes, GL_STATIC_DRAW);

	//Так как VAO уже создан, то можно сразу связать с ним
	glBindVertexArray(vaoID);
	//Собственно связь
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Подключение атрибута
	glEnableVertexAttribArray(0);
}

void 
Drawable::setColors(glm::vec3* colors, size_t count)
{
	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), colors,
		GL_STATIC_DRAW);
	glBindVertexArray(vaoID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
}

void 
Drawable::setIndexes(GLuint* indexes, size_t count)
{
	indexesCount = count;
	glBindVertexArray(vaoID);
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer); // Генерация одного объекта буфера вершин
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer); //Привязка элементного буфера
	//Загрузка индексов в используемый элементный буфер
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indexes, GL_STATIC_DRAW);
}


