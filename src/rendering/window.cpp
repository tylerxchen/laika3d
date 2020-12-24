#include "window.hpp"

#include <stdexcept>

using namespace tc3d::rendering;

Window::Window() {
  glewExperimental = true;
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win = glfwCreateWindow(1024, 768, "tc3d", nullptr, nullptr);

  if (win == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to open a GLFW window. Check your version of OpenGL");
  }

  glfwMakeContextCurrent(win);
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Failed to initialize GLEW");
  }
}

Window::~Window() {
  glfwDestroyWindow(win);
}

void Window::loop() {
  if (!callback) {
    return;
  }

  glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    callback();
    glfwSwapBuffers(win);
    glfwPollEvents();
  } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(win) == 0);
}
