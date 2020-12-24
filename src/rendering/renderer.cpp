#include "renderer.hpp"

#include <stdexcept>

using namespace tc3d::rendering;

Renderer::Renderer() {
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
}

void Renderer::draw(const VertexBuffer& vbuf, const IndexBuffer& ibuf) const {
  glEnableVertexAttribArray(0);
  vbuf.bind();
  ibuf.bind();
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
