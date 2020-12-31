#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>

#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"

namespace laika3d {
  class Model {
    public:
      Model(const std::string& filepath);
      Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

      void set_translation(float x, float y, float z);
      void set_rotation_x(float angle);
      void set_rotation_y(float angle);
      void set_rotation_z(float angle);
      void set_scale(float x, float y, float z);

      std::size_t v_index_count() const { return v_indices->count(); }
      std::size_t vt_index_count() const { return vt_indices->count(); }
      std::size_t vn_index_count() const { return vn_indices->count(); }

      glm::mat4 get_model() const { return model; };

      void bind() const;
      void unbind() const;

    private:
      void calc_model_mat();
      void init_mats();

      std::unique_ptr<VertexBuffer> vbuf;
      std::unique_ptr<IndexBuffer> v_indices;
      std::unique_ptr<IndexBuffer> vt_indices;
      std::unique_ptr<IndexBuffer> vn_indices;

      glm::mat4 translation;
      glm::mat4 rotation;
      glm::mat4 scaling;
      glm::mat4 model;
  };
}
