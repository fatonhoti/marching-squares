#pragma once

// stdlib
#include <string_view>
#include <optional>

namespace renderer {

struct Shader {
    unsigned int handle;
};

std::optional<Shader> createShader(std::string_view vertexShader, std::string_view fragmentShader);

} // end namespace "renderer"
