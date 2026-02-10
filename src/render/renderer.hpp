#pragma once
#include <memory>
#include <array>

using GLuint = unsigned int;

class ShaderProgram;

class Renderer {
private:
    std::unique_ptr<ShaderProgram> shaderProgram;

    bool success;

    GLuint vaoID = 0;
    GLuint vboID = 0;
    GLuint eboID = 0;

    /* uniforms */
    GLuint projLoc = 0;
    GLuint modelLoc = 0;
    GLuint colorLoc = 0;

    int fieldWidth;
    int fieldHeight;

    float cellWidth;
    float cellHeight;

public:
    Renderer();
    ~Renderer();

    const bool getSuccessInfo() const { return success; }

    void setFieldSize(const int& width, const int& height);

    void beginFrame();
    void endFrame();

    void drawCell(const std::array<int, 2>& cellPos, const std::array<int, 3>& cellColor);

private:
    void init();
};