#include "shader.hpp"

// vendor
#include <fmt/format.h>
#include "glad2/gl.h"

// stdlib
#include <fstream>
#include <sstream>

namespace renderer {

std::optional<Shader> createShader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath) {

    auto readFile = [](std::string_view path) {
        std::ifstream file{std::string(path)};
        if (!file.is_open()) {
            fmt::println("Failed to open shader file: {}", path);
            return std::string{};
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    };

    const std::string vertexCode = readFile(vertexShaderPath);
    const std::string fragmentCode = readFile(fragmentShaderPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        return std::nullopt;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return Shader{ .handle = shaderProgram };
}

} // end namespace "renderer"
