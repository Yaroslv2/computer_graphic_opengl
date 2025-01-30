#include "Window.h"

#include <iostream>

Window Window::instanse = Window();

Window::Window() : window(nullptr),
                       height(0),
                       width(0),
                       title("")
{}

Window&
Window::getInstanse()
{
    return Window::instanse;
}

bool 
Window::createWindow(int width, int height, std::string title)
{
    this->height = height;
    this->width = width;
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error occured in Window::init(): window was not created" 
                  << std::endl;

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
Window::resize(int width, int height)
{
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);
}

void 
Window::close()
{
    glfwSetWindowShouldClose(window, 1);
}

bool 
Window::isWindowClosed()
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