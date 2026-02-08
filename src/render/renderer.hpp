#pragma once
#include <memory>
#include <array>

using GLuint = unsigned int;

class ShaderProgram;

class Renderer {
private:
    std::unique_ptr<ShaderProgram> shaderProgram;
    GLuint vaoID = 0;
    GLuint vboID = 0;

    bool success;

    void init();

    void initQuad();

public:
    Renderer();
    ~Renderer();

    void beginFrame();

    void drawCell(const int& weight, const int& height, const std::array<int, 2>& cellPos, const std::array<int, 3>& cellColor);

    void endFrame();

    const bool getSuccessInfo() const { return success; }
};