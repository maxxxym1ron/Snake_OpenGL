namespace shaders {
    /* vertex shader code */
    constexpr const char* vertSource = R"(#version 330 core
    layout (location = 0) in vec2 vertexPos;
    layout (location = 1) in vec3 vertexCol;
    out vec4 vColor;
    void main() {
        gl_Position = vec4(vertexPos.xy, 0.0f, 1.0f);
        vColor = vec4(vertexCol.xyz, 1.0f);
    }
    )";

    /* fragment shader code */
    constexpr const char* fragSource = R"(#version 330 core
    in vec4 vColor;
    out vec4 FragColor;
    void main() {
        FragColor = vColor;
    }
    )";
}