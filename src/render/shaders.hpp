namespace shaders {
    /* 1st program */
    constexpr const char* vertSource = R"(#version 330 core
    layout (location = 0) in vec2 vertexPos;

    uniform mat4 model;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * model * vec4(vertexPos.xy, 0.0, 1.0);
    }
    )";

    constexpr const char* fragSource = R"(#version 330 core
    out vec4 FragColor;

    uniform vec3 color;

    void main() {
        FragColor = vec4(color.xyz, 1.0);
    }
    )";
}