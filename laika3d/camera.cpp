#include "camera.hpp"

using namespace laika3d;

void Camera::move(float x, float y, float z) {
  view = glm::translate(glm::mat4(), glm::vec3(x, y, z));
}
