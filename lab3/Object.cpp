#include "Object.h"

#include "OpenGLManager.h"

Object::Object() : mode(GL_TRIANGLES), vaoID(0), 
									   indexCount(0), 
									   vertexCount(0), 
									   shaderProgramID(-1),
									   matrixTransform(glm::mat4(1.0f))
{
	glGenVertexArrays(1, &vaoID);
};

void 
Object::render()
{
	//Выбираем шейдерную программу
	glUseProgram(shaderProgramID);

	//привязка матрицы преобразований
	GLuint matrixID = glGetUniformLocation(shaderProgramID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &matrixTransform[0][0]);

	//Активируем массив вершин
	glBindVertexArray(vaoID);
	//Если индексы есть - рисуем по ним
	if (indexCount > 0)
	{
		glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(mode, 0, vertexCount);
	}
}

void 
Object::setMode(GLuint mode)
{
	this->mode = mode;
}

void 
Object::setShaderProgram(GLuint shaderProgram)
{
	shaderProgramID = shaderProgram;
}

void Object::setMatrixTransform(glm::mat4 matrix)
{
	matrixTransform = matrix;
}

void 
Object::loadCoords(glm::vec3* verteces, size_t count)
{
	//Сохранение размера массива
	vertexCount = count;
	//Создание VBO
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), verteces, GL_STATIC_DRAW);

	//Так как VAO уже создан, то можно сразу связать с ним
	glBindVertexArray(vaoID);
	//Собственно связь
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Подключение атрибута
	glEnableVertexAttribArray(0);
}

void 
Object::loadColors(glm::vec3* colors, size_t count)
{
	//Размер сохранять не требуется – важно только число вершин
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
Object::loadIndexes(GLuint* indices, size_t count)
{
	indexCount = count;
	glBindVertexArray(vaoID);
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer); // Генерация одного объекта буфера вершин
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer); //Привязка элементного буфера
	//Загрузка индексов в используемый элементный буфер
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof
	(GLuint), indices, GL_STATIC_DRAW);
}

void Object::loadShaders(const char* vect, const char* frag)
{
	// Переменные под результат компиляции программы
	GLint result = GL_FALSE;
	int infoLogLength;
	//Создание шейдерной программы
	shaderProgramID = glCreateProgram();
	//Загрузка текстов шейдеров из файлов
	std::string vstext = OpenGLManager::getInstanse()
		.loadShader(vect);
	const char* vertex_shader = vstext.c_str();
	std::string fstext = OpenGLManager::getInstanse()
		.loadShader(frag);;
	const char* fragment_shader = fstext.c_str();
	//Создание вершинного шейдера
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	//Проверка результата компиляции
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLogLength);
	//Вывод сообщения об ошибке если что-то пошло не так
	if (infoLogLength > 0)
	{
		char* errorMessage = new char[infoLogLength + 1];
		glGetShaderInfoLog(vs, infoLogLength, NULL, errorMessage);
		std::cout << errorMessage;
		delete errorMessage;
	}

	//Аналогично с фрагментным шейдером
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		char* errorMessage = new char[infoLogLength + 1];
		glGetShaderInfoLog(fs, infoLogLength, NULL, errorMessage);
		std::cout << errorMessage;
		delete errorMessage;
	}

	//Сборка программы
	glAttachShader(shaderProgramID, vs);
	glAttachShader(shaderProgramID, fs);

	//Тонкий момент – тут жёстко связываются названия входных переменных в шейдерах со атрибутами массива вершин
	//Это лучше вынести в отдельные функции для большей универсальности.
	//Однако так как это пример, то оставлено так
	glBindAttribLocation(shaderProgramID, 0, "vertex_position");
	glBindAttribLocation(shaderProgramID, 1, "vertex_color");

	//Компоновка шейдерной программы
	glLinkProgram(shaderProgramID);
}


