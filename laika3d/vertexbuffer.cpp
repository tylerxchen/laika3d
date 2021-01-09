#include "vertexbuffer.hpp"
#include <GL/glew.h>

#include <iostream>

using namespace laika3d;

VertexBuffer::VertexBuffer(const std::vector<Vertex>& buf)
  : vbuf(buf) {
  glGenBuffers(1, &renderer_id);
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
  glBufferData(GL_ARRAY_BUFFER, vbuf.size() * sizeof(Vertex), vbuf.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
