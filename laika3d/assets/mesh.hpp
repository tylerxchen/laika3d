#pragma once

#include "resource.hpp"
#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"

#include <string>
#include <memory>

namespace laika3d {
  class Mesh : public Resource {
    public:
      Mesh(const std::string& file_path);
      ~Mesh();

      std::size_t v_index_count() const { return v_indices->count(); }
      std::size_t vt_index_count() const { return vt_indices->count(); }
      std::size_t vn_index_count() const { return vn_indices->count(); }

      void bind() const;
      void unbind() const;

      std::unique_ptr<VertexBuffer> vbuf;
      std::unique_ptr<IndexBuffer> v_indices;
      std::unique_ptr<IndexBuffer> vt_indices;
      std::unique_ptr<IndexBuffer> vn_indices;
  };
}
