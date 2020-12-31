#include "indexbuffer.hpp"
#include <GL/glew.h>

using namespace laika3d;

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& buf)
  : ibuf(buf) {
  glGenBuffers(1, &renderer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibuf.size() * sizeof(unsigned int), ibuf.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void IndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
