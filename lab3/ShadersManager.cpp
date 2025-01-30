#include "ShadersManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

ShadersManager ShadersManager::instanse = ShadersManager::ShadersManager();

ShadersManager::ShadersManager()
{

}

ShadersManager& ShadersManager::getInstanse()
{
    return instanse;
}

void ShadersManager::init()
{
    createShaderProgram("mono_vs.glsl", "mono_fs.glsl", "mono");
    createShaderProgram("grad_vs.glsl", "grad_fs.glsl", "gradient");
    createShaderProgram("matrix_vs.glsl", "mono_fs.glsl", "matrix");
}

GLuint ShadersManager::createShaderProgram(const char* vsFile, const char* fsFile, std::string name)
{
    // Переменные под результат компиляции программы
    GLint result = GL_FALSE;
    int infoLogLength;
    //Создание шейдерной программы
    GLuint shaderProgramID = glCreateProgram();
    //Загрузка текстов шейдеров из файлов
    std::string vstext = loadShader(vsFile);
    const char* vertex_shader = vstext.c_str();
    std::string fstext = loadShader(fsFile);
    const char* fragment_shader = fstext.c_str();

    //Создание вершинного шейдера
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    //Аналогично с фрагментным шейдером
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLint success;
    GLchar infoLog[512];

    // Проверка компиляции вершинного шейдера
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Проверка компиляции фрагментного шейдера
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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

    // Проверка линковки программы
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    setShaderProgram(shaderProgramID, name);
    return shaderProgramID;
}

bool ShadersManager::contains(std::string name)
{
    if (shaders.count(name))
        return true;
    return false;
}

GLuint 
ShadersManager::getShaderProgram(std::string name)
{
    if (!contains(name))
    {
        return -1;
    }
    return shaders[name];
}

void ShadersManager::setShaderProgram(GLuint shaderProgramID, std::string name)
{
    shaders.insert({name, shaderProgramID});
}

std::string ShadersManager::loadShader(const char* filename)
{
    std::string shader;
    std::ifstream file(filename, std::ios::in);
    if (file.is_open())
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        shader = sstr.str();
        file.close();
    }
    return shader;
}