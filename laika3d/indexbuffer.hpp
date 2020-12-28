#pragma once

#include <vector>

namespace laika3d {
  class IndexBuffer {
    public:
      IndexBuffer();
      IndexBuffer(const std::vector<unsigned int>& buf);
      ~IndexBuffer();

      void bind() const;
      void unbind() const;
      inline unsigned int count() const { return ibuf.size(); }
      
    private:
      void init_gl();

      unsigned int renderer_id;
      std::vector<unsigned int> ibuf;
  };
}
