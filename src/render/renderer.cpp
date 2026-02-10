#include "renderer.hpp"

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_program.hpp"
#include "shaders.hpp"
#include "quad_vertices.hpp"

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
    if (vaoID) glDeleteVertexArrays(1, &vaoID);
    if (vboID) glDeleteBuffers(1, &vboID);
    if (eboID) glDeleteBuffers(1, &eboID);
}

void Renderer::init() {
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    /* Create EBO */
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices, GL_STATIC_DRAW);

    /* Allocate memory for common cells */
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Setting VAO */
    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /* End VAO */

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    /* projection -- uniform */
    glm::mat4 projection = glm::ortho(
        0.0f, 2.f,
        0.0f, 2.f
    );
    GLuint shaderProgramID = shaderProgram->getID();

    glUseProgram(shaderProgramID);
    GLint projLoc = glGetUniformLocation(shaderProgramID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(0);
}

/* preparation GPU to new frame */
void Renderer::beginFrame() { 
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram->use();
    glBindVertexArray(vaoID);
}

/* Completion */
void Renderer::endFrame() {
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::drawCell(const std::array<int, 2>& cellPos, const std::array<int, 3>& cellColor) {
    /* cell color */
    float r = static_cast<float>(cellColor[0]) / 255.f;
    float g = static_cast<float>(cellColor[1]) / 255.f;
    float b = static_cast<float>(cellColor[2]) / 255.f;


    /* glm shit */
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(
        cellPos[0] * cellWidth + cellWidth * 0.5f,
        cellPos[1] * cellHeight + cellHeight * 0.5f,
        0.f
    ));
    model = glm::scale(model, glm::vec3(cellWidth));

    /* uniforms */
    if (!modelLoc)
        modelLoc = glGetUniformLocation(shaderProgram->getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    if (!colorLoc)
        colorLoc = glGetUniformLocation(shaderProgram->getID(), "color");
    glUniform3f(colorLoc, r, g, b);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::setFieldSize(const int& width, const int& height) {
    fieldWidth = width; 
    fieldHeight = height; 
    
    cellWidth = 2.f / width;
    cellHeight = 2.f / height;
}