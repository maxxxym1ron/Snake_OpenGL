#include "renderer.hpp"

#include <iostream>
#include <glad/glad.h>

#include "shader_program.hpp"
#include "shaders.hpp"

/* Create shader program and initialize vao and vbo */
Renderer::Renderer(): success(false) {
    shaderProgram = std::make_unique<ShaderProgram>(shaders::vertSource, shaders::fragSource);

    if(!shaderProgram->getSuccessInfo()) {
        std::cout << "ShaderProgram creation failed" << std::endl;
    }
    else {
        init();
        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

        success = true;
    }
}

Renderer::~Renderer() {
    if (vaoID) {
        glDeleteVertexArrays(1, &vaoID);
    }
    if (vboID) {
        glDeleteBuffers(1, &vboID);
    }
}

void Renderer::init() {
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    /* allocate memory on GPU */
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    /* Setting VAO */
    glBindVertexArray(vaoID);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

/* preparation GPU to new frame */
void Renderer::beginFrame() { 
    glClear(GL_COLOR_BUFFER_BIT);
}

/* release frame */
void Renderer::endFrame() { }

void Renderer::drawCell(const int& weight, const int& height,
        const std::array<int, 2>& cellPos, const std::array<int, 3>& cellColor) {
    /* cell color */
    float r = static_cast<float>(cellColor[0]) / 255.f;
    float g = static_cast<float>(cellColor[1]) / 255.f;
    float b = static_cast<float>(cellColor[2]) / 255.f;

    /* cell size */
    float cellW = 2.0f / weight;
    float cellH = 2.0f / height;
    
    /* Left bottom */
    float left = -1.0f + cellW * static_cast<float>(cellPos[0]);
    float bottom = -1.0f + cellH * static_cast<float>(cellPos[1]);
    /* Right top */
    float right = left + cellW;
    float top = bottom + cellH;

    const float quadVertices[30] = {
        left,  bottom,   r, g, b,
        right, bottom,   r, g, b,
        left,  top,      r, g, b,

        right, bottom,   r, g, b,
        left,  top,      r, g, b,
        right, top,      r, g, b
    };

    shaderProgram->use();

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quadVertices), quadVertices);
    glBindVertexArray(vaoID);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}