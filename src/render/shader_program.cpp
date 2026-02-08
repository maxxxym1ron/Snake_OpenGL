#include "shader_program.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(const char* vertSource, const char* fragSource)
    : compilationSuccess(true) {
    int success = 0;

    /* Compile shaders */
    GLuint vertShaderID = createShader(GL_VERTEX_SHADER, vertSource, success);
    GLuint fragShaderID = createShader(GL_FRAGMENT_SHADER, fragSource, success);

    /* Create ShaderProgram */
    if (compilationSuccess)
        createProgram(vertShaderID, fragShaderID, success);
}

GLuint ShaderProgram::createShader(GLenum typeShader, const char*& shaderSource, int& success) {
    GLuint shaderID = glCreateShader(typeShader);
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER::" << static_cast<int>(typeShader) << "_ID::COMPILATION_FAILED" << std::endl;
        compilationSuccess = false;
    }

    return shaderID;
}

void ShaderProgram::createProgram(const GLenum vertShaderID, const GLenum fragShaderID, int& success) {
    ID = glCreateProgram();
    glAttachShader(ID, vertShaderID);
    glAttachShader(ID, fragShaderID);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED" << std::endl;
        compilationSuccess = false;
    }

    /* shader objects not needed anymore */
    glDetachShader(ID, vertShaderID);
    glDetachShader(ID, fragShaderID);
    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
}