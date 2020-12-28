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

      void translate(float x, float y, float z);
      void rotate_x(float angle);
      void rotate_y(float angle);
      void rotate_z(float angle);
      void scale(float x, float y, float z);

      std::size_t index_count() const { return ibuf->count(); }

      glm::mat4 mat();

      void bind() const;
      void unbind() const;

    private:
      void calc_model_mat();
      void init_mats();

      std::unique_ptr<VertexBuffer> vbuf;
      std::unique_ptr<IndexBuffer> ibuf;

      glm::mat4 translation;
      glm::mat4 rotation;
      glm::mat4 scaling;
      glm::mat4 model;
  };
}
