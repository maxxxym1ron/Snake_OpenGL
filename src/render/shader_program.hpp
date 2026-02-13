#pragma once
#include <glad/glad.h>

class ShaderProgram {
    GLuint ID;
    bool compilationSuccess;

    GLuint createShader(const GLenum typeShader, const char*& shaderSource, int& success, const bool& isFirst);
    void createProgram(const GLenum vertShaderID, const GLenum fragShaderID, int& success);

public:
    ShaderProgram(const char* vertSource, const char* fragSource);
    ~ShaderProgram() { glDeleteProgram(ID); }

    bool getSuccessInfo() const { return compilationSuccess; }

    void use() { glUseProgram(ID); }

    GLuint getID() { return ID; }
};