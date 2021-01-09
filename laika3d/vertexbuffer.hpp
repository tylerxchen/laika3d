#pragma once

#include <vector>

namespace laika3d {
  struct Vertex {
    float x;
    float y;
    float z;
    float norm_x;
    float norm_y;
    float norm_z;
    float tex_x;
    float tex_y;
    float tex_z;
  };

  class VertexBuffer {
    public:
      VertexBuffer();
      VertexBuffer(const std::vector<Vertex>& buf);
      ~VertexBuffer();

      void bind() const;
      void unbind() const;

    private:
      void init_gl();

      unsigned int renderer_id;
      std::vector<Vertex> vbuf;
  };
}
