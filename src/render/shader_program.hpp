#pragma once
#include <glad/glad.h>

class ShaderProgram {
    GLuint ID;
    bool compilationSuccess;

    GLuint createShader(const GLenum typeShader, const char*& shaderSource, int& success);
    void createProgram(const GLenum vertShaderID, const GLenum fragShaderID, int& success);

public:
    ShaderProgram(const char* vertSource, const char* fragSource);
    ~ShaderProgram() { glDeleteProgram(ID); }

    void use() { glUseProgram(ID); }

    const bool getSuccessInfo() const { return compilationSuccess; }

    const GLuint getID() { return ID; }
};