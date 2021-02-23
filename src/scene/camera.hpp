#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace laika3d {
  class Camera {
    public:
      Camera();
      Camera(float fovy, float aspect, float near, float far);

      void translate(float delta_x, float delta_y, float delta_z);
      void rotate_x(float delta_theta);
      void rotate_y(float delta_theta);

      void set_translation(float x, float y, float z);
      void set_rotation_x(float theta);
      void set_rotation_y(float theta);

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
