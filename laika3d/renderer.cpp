#include "renderer.hpp"

#include <stdexcept>
#include <iostream>

using namespace laika3d;

namespace laika3d {
  void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL message: " << message << std::endl;
  }
}

Renderer::Renderer(unsigned int width, unsigned int height) {
  glewExperimental = true;
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win = glfwCreateWindow(width, height, "laika3d", nullptr, nullptr);

  if (win == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to open a GLFW window. Check your version of OpenGL");
  }

  glfwMakeContextCurrent(win);
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Failed to initialize GLEW");
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(message_callback, nullptr);
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
}

Renderer::~Renderer() {
  glfwDestroyWindow(win);
}

void Renderer::loop() {
  if (!callback) {
    return;
  }

  glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    callback();
    glfwSwapBuffers(win);
    glfwPollEvents();
  } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(win) == 0);
}

void Renderer::draw(const Model& m, const Shader& s, const Camera& c) const {
  glm::mat4 mvp = c.get_proj() * c.get_view() * m.get_model();
  glEnableVertexAttribArray(0);
  m.bind();
  s.bind();
  glUniformMatrix4fv(s.get_mvp_id(), 1, GL_FALSE, &mvp[0][0]);

  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    static_cast<void*>(0)
  );

  glDrawElements(
    GL_TRIANGLES,
    m.index_count(),
    GL_UNSIGNED_INT,
    static_cast<void*>(0)
  );

  glDisableVertexAttribArray(0);
}
