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

Renderer::Renderer() {
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(message_callback, nullptr);
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
}

void Renderer::draw(const VertexBuffer& vbuf, const IndexBuffer& ibuf, const Shader& s) const {
  glEnableVertexAttribArray(0);
  vbuf.bind();
  ibuf.bind();
  s.bind();
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
    ibuf.count(),
    GL_UNSIGNED_INT,
    static_cast<void*>(0)
  );
  glDisableVertexAttribArray(0);
}
