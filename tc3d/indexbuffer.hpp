#pragma once

#include <vector>

namespace tc3d {
  namespace rendering {
    class IndexBuffer {
      public:
        IndexBuffer(const std::vector<unsigned int>& buf);
        IndexBuffer(std::vector<unsigned int>&& buf);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;
        inline unsigned int count() const { return ibuf.size(); }
        
      private:
        void init_gl();

        unsigned int renderer_id;
        const std::vector<unsigned int> ibuf;
    };
  }
}
