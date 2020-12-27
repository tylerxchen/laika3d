#pragma once

#include <vector>

namespace laika3d {
  struct Vertex {
    float x;
    float y;
    float z;
  };

  class VertexBuffer {
    public:
      VertexBuffer(const std::vector<Vertex>& buf);
      ~VertexBuffer();

      void bind() const;
      void unbind() const;

    private:
      void init_gl();

      unsigned int renderer_id;
      const std::vector<Vertex> vbuf;
  };
}