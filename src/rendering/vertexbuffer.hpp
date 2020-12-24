#pragma once

#include <vector>

namespace tc3d {
  namespace rendering {
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
}
