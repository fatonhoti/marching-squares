#include <fmt/format.h>
#include <GLFW/glfw3.h>

namespace {

bool running = false;

void error_callback(int code, const char* description) {
    fmt::println(stderr, "GLFW error {}: {}", code, description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)window;
    (void)scancode;
    (void)action;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        ::running = false;
    }
}

}

int main() {
    glfwSetErrorCallback(::error_callback);

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "marching-squares", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, ::key_callback);

    fmt::println("OpenGL {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    ::running = true;
    while (::running) {
        glfwPollEvents();

        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwSetWindowShouldClose(window, true);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
