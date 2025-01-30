#include "OpenGLManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "libsInclude.h"
#include "Window.h"
#include "Callbacks.h"
#include "SceneManager.h"
#include "ShadersManager.h"

OpenGLManager OpenGLManager::instanse = OpenGLManager::OpenGLManager();

OpenGLManager::OpenGLManager()
{}

OpenGLManager&
OpenGLManager::getInstanse()
{
    return instanse;
}

bool
OpenGLManager::init()
{
    // initialize glfw
    if (!glfwInit()) {
        std::cout << "Error was occured in OpenGLManager::init: GLFW3 was not started" << std::endl;
        return false;
    }

    // create window
    if (!Window::getInstanse().createWindow(1000, 600, "lab3"))
    {
        return false;
    }
    Window::getInstanse().setActive();

    // intialize glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Error was occured in OpenGLManager::init (GLEW): "
            << glewGetErrorString(err)
            << std::endl;
        glfwTerminate();
        return false;
    }

    ShadersManager::getInstanse().init();

    SceneManager::getInstanse().setCurrentSceneIdx(0);

    setCallbacks();


    return true;
}

void
OpenGLManager::setCallbacks()
{
    glfwSetWindowSizeCallback(Window::getInstanse().getGLFWwindow(),
        &Callbacks::windowResize);
    glfwSetKeyCallback(Window::getInstanse().getGLFWwindow(),
        &Callbacks::keyAction);
}

std::string
OpenGLManager::loadShader(const char* filename)
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