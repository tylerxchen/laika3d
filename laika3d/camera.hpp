#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace laika3d {
  class Camera {
    public:
      Camera(float fovy, float aspect, float near, float far) : projection(glm::perspective(fovy, aspect, near, far)) {}

      void move(float x, float y, float z);

    private:
      glm::mat4 projection;
  };
}
