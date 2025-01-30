#include "Window.h"

#include <iostream>

Window Window::instanse = Window::Window();

Window& Window::getInstance()
{
    return instanse;
}

Window::Window() : window(nullptr), height(0), width(0), title("")
{}

Window::~Window()
{}

bool
Window::createWindow(int width, int height, std::string title)
{
    this->height = height;
    this->width = width;
    /// glfwCreateWindow()
    /// функция для создания окна, принимает следующие параметры:
    /// int width -- ширина окна
    /// int heignt -- высота окна
    /// char* title -- заголовок окна
    /// GLFWmonitor* monitor -- монитор, используемый для полноэкранного режима, или NULL для оконного
    /// GLFWwindow* share -- окно, с которым необходимо делиться ресурсами
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error occured in Window::init(): window was not created" << std::endl;

        return false;
    }

    return true;
}

GLFWwindow*& 
Window::getGLFWwindow()
{
    return window;
}

void
Window::close()
{
    glfwSetWindowShouldClose(window, 1);
}

void 
Window::resize(int width, int height)
{
    instanse.height = height;
    instanse.width = width;
    glViewport(0, 0, width, height);
}

bool
Window::isClosed()
{
    return glfwWindowShouldClose(window);
}

void
Window::setActive()
{
    glfwMakeContextCurrent(window);
}

int 
Window::getHeight()
{
    return height;
}

int
Window::getWidth()
{
    return width;
}