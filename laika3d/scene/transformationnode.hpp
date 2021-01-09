#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "scenenode.hpp"

namespace laika3d {
  class TransformationNode : public SceneNode {
    public:
      TransformationNode();
      ~TransformationNode();

      glm::mat4 get_model_matrix() const;

      void set_scale(glm::vec3 s);

      void set_translation(glm::vec3 t);

      void rotate_x(float angle);
      void rotate_y(float angle);
      void rotate_z(float angle);
      void reset_rotation();

    private:
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
  };
}
