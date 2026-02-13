#include <glad/glad.h>
#include "window.hpp"
#include "logo.hpp"

#include <iostream>
#include <string>

Window::Window(int width, int height, bool fullscreen) : terminated(false) {
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed" << std::endl;
        exit(1);
    }

    /* Set OpenGL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create window */ // 4 param -- is fullcreen or no
    m_handle = glfwCreateWindow(width, height, "Snake | FPS: ", nullptr, nullptr);
    if (!m_handle) {
        std::cout << "GLFW: window creation failed" << std::endl;
        terminateWindow();
        exit(2);
    }

    glfwMakeContextCurrent(m_handle);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD: loading process failed." << std::endl;
        terminateWindow();
        exit(3);
    }

    /* Get monitor info */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    m_mWidth = mode->width;
    m_mHeight = mode->height;
    m_mRefreshRate = mode->refreshRate;

    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;

    glfwSetWindowPos(m_handle, m_mWidth / 2 - m_width / 2, m_mHeight / 2 - m_height / 2);
    glfwSetWindowAttrib(m_handle, GLFW_RESIZABLE, GLFW_FALSE);
    glfwSwapInterval(1);

    GLFWimage icon;
    icon.width = 48;
    icon.height = 48;
    icon.pixels = iconData;
    glfwSetWindowIcon(m_handle, 1, &icon);

    glfwSetErrorCallback(&Window::errorCallback);
    glfwSetKeyCallback(m_handle, &Window::keyCallback);
}

void Window::setTitle(const int& fps, const int& length) {
    std::string title = "Snake | Length: " + std::to_string(length) + " | FPS: "+ std::to_string(fps);
    glfwSetWindowTitle(m_handle, title.c_str());
}

void Window::close() const { glfwSetWindowShouldClose(m_handle, GLFW_TRUE); }
bool Window::shouldClose() { return static_cast<bool>(glfwWindowShouldClose(m_handle)); }

void Window::pollEvents() { glfwPollEvents(); }
void Window::swapBuffers() { glfwSwapBuffers(m_handle); }

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

void Window::errorCallback(const int error_code, const char *description) {
    std::cerr << "ERROR: " << error_code << "\nDESCRIPTION: " << description;
}