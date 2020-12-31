#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace laika3d {
  class Camera {
    public:
      Camera(float fovy, float aspect, float near, float far);

      void translate(float x, float y, float z);
      void rotate_x(float angle);
      void rotate_y(float angle);

      glm::mat4 get_view() const { return view; }
      glm::mat4 get_proj() const { return projection; }

    private:
      void calc_view_mat();
      glm::mat4 translation;
      glm::mat4 rotation;

      glm::mat4 projection;
      glm::mat4 view;
  };
}
