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

      void bind() const;
      void unbind() const;

      std::unique_ptr<VertexBuffer> vbuf;
      std::unique_ptr<IndexBuffer> v_indices;
  };
}
