#include <glad/glad.h>
#include <iostream>
#include <string>

#include "window.hpp"

Window::Window(int wWidth_, int wHeight_, bool fullscreen_) : terminated(false) {

    /* init GLFW */
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed" << std::endl;
        exit(1);
    }

    /* Set version of OpenGL */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create window */ // 4 param -- is fullcreen or no
    m_handle = glfwCreateWindow(wWidth_, wHeight_, "Snake | FPS: ", nullptr, nullptr);
    if (!m_handle) {
        std::cout << "GLFW: window creation failed" << std::endl;
        terminateWindow();
        exit(2);
    }

    glfwSetWindowAttrib(m_handle, GLFW_RESIZABLE, GLFW_FALSE);

    /* Get monitor info */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    mWidth = mode->width;
    mHeight = mode->height;
    mRefreshRate = mode->refreshRate;

    wWidth = wWidth_;
    wHeight = wHeight_;
    fullscreen = fullscreen_;

    glfwSetWindowPos(m_handle, mWidth / 2 - wWidth / 2, mHeight / 2 - wHeight / 2);

    glfwMakeContextCurrent(m_handle);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD: loading process failed" << std::endl;
        terminateWindow();
        exit(3);
    }

    glfwSetKeyCallback(m_handle, &Window::keyCallback);
}

void Window::close() const { glfwSetWindowShouldClose(m_handle, GLFW_TRUE); }
bool Window::shouldClose() { return static_cast<bool>(glfwWindowShouldClose(m_handle)); }

void Window::pollEvents() { glfwPollEvents(); }
void Window::swapBuffers() { glfwSwapBuffers(m_handle); }

void Window::setTitle(const int& fps) {
    std::string title = "Snake | FPS: " + std::to_string(fps);
    glfwSetWindowTitle(m_handle, title.c_str());
}

void Window::terminateWindow() { 
    if (!terminated) {
        glfwTerminate(); 
        terminated = true;
    }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        m_keys[key] = 1;
    if (action == GLFW_RELEASE)
        m_keys[key] = 0;
}