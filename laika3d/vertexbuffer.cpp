#include "vertexbuffer.hpp"
#include <GL/glew.h>

using namespace laika3d;

VertexBuffer::VertexBuffer() {
  init_gl();
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& buf)
  : vbuf(buf) {
  init_gl();
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::append(const Vertex& v) {
  vbuf.push_back(v);
}

void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::init_gl() {
  glGenBuffers(1, &renderer_id);
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
  glBufferData(GL_ARRAY_BUFFER, vbuf.size() * sizeof(Vertex), vbuf.data(), GL_STATIC_DRAW);
}
