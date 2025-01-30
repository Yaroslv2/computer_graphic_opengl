#include "Drawable.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

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

void Drawable::loadModelFromFile(const char* path)
{
    //Временные массивы для хранения индексов и значений из файла
    std::vector< unsigned int > vertexIndices, vtIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_textures;
    std::vector< glm::vec3 > temp_normals;
    //Строка для хранения токенов из файла
    std::string buf;
    //Буфер, хранящий содержимое файла
    std::stringstream sstr;
    //Переменная для корректной работы с неизвестным числом вершин в грани
    bool cont = false;

    //Считывание файла
    std::ifstream file(path, std::ios::in);
    if (file.is_open())
    {
        sstr << file.rdbuf();
        file.close();
    }
    else
        std::cout << "ERROR: cannot open file " << path << std::endl;

    //Очистка выходных массивов
    normals.clear();
    vertexes.clear();
    texture.clear();
    //Попытка считать токен из файла
    while (cont || sstr >> buf)
    {
        cont = false;

        //Обработка координат
        if (buf == "v")
        {
            glm::vec3 vertex;
            sstr >> vertex.x;
            sstr >> vertex.y;
            sstr >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        //Обработка текстурных координат
        else if (buf == "vt")
        {
            glm::vec2 texture;
            sstr >> texture.x;
            sstr >> texture.y;
            temp_textures.push_back(texture);
        }
        else if (buf == "vn")
        {
            glm::vec3 normal;
            sstr >> normal.x;
            sstr >> normal.y;
            sstr >> normal.z;
            temp_normals.push_back(normal);
        }
        //Обработка граней
        else if (buf == "f")
        {
            //Временные массивы для хранения информации о грани
            std::vector<std::string> tvertexes;
            std::vector<int> vertindexes;
            while (!cont)
            {
                //Считывается токен
                sstr >> buf;
                //Если токен содержит данные о вершине – она записывается в массив
                if (buf.find('/') != std::string::npos)
                    tvertexes.push_back(buf);
                //Если токен – начало следующей строки, он сохраняется и начинается обработка грани
                else
                {
                    //Для каждой из сохранённых вершин производится парсингданных
                    for (std::string vert : tvertexes)
                    {
                        std::replace(vert.begin(), vert.end(), '/', ' ');
                        std::stringstream tmpstream(vert);
                        int v, vt, n;
                        tmpstream >> v;
                        tmpstream >> vt;
                        tmpstream >> n;
                        //Индексы заносятся в временный массив
                        vertindexes.push_back(v);
                        vertindexes.push_back(vt);
                        vertindexes.push_back(n);
                    }
                    //Первые три вершины заносятся в массивы индексов
                    for (int i = 0; i < 3; i++)
                    {
                        vertexIndices.push_back(vertindexes[i * 3 + 0]);
                        vtIndices.push_back(vertindexes[i * 3 + 1]);
                        normalIndices.push_back(vertindexes[i * 3 + 2]);
                    }
                    //Дальше сложнее – если ещё остались вершины, надо и их занести
                    //Но надо преобразовать из веера треугольников в набор треугольников
                    size_t tmpsize = tvertexes.size();
                    if (tmpsize > 3)
                    {
                        //Для каждой из вершин добавляются три вершины, образующие треугольник
                        for (int i = 3; i < tmpsize; i++)
                        {
                            vertexIndices.push_back(vertindexes[0]);
                            vtIndices.push_back(vertindexes[1]);
                            normalIndices.push_back(vertindexes[2]);
                            vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
                            vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
                            normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
                            vertexIndices.push_back(vertindexes[i * 3 + 0]);
                            vtIndices.push_back(vertindexes[i * 3 + 1]);
                            normalIndices.push_back(vertindexes[i * 3 + 2]);
                        }
                    }
                    //Чтобы не потерялся считанный токен, ставится флаг о том, что он сохранён
                    cont = true;
                }
            }
        }
    }

    // Теперь обработка массивов индексов и создание выходных массивов
        // Для каждой вершины в массиве значения, соответствующие
        // вершине под указанным индексом заносятся в выходной массив
    size_t tmpsize = vertexIndices.size();
    for (unsigned int i = 0; i < tmpsize; i++)
    {
        //Надо учесть, что индексы в файле начинаются с 1!
        glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
        vertexes.push_back(vertex);
        glm::vec3 normal = temp_normals[normalIndices[i] - 1];
        normals.push_back(normal);
        glm::vec2 vt = temp_textures[vtIndices[i] - 1];
        texture.push_back(vt);
    }

    setVertexes(vertexes.data(), vertexes.size());
}


