#include "camera.hpp"

using namespace laika3d;

Camera::Camera(float fovy, float aspect, float near, float far)
  : projection(glm::perspective(fovy, aspect, near, far)), translation(1.0f), rotation(1.0f) {
  calc_view_mat();
}


void Camera::translate(float x, float y, float z) {
  translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_view_mat();
}

void Camera::rotate_x(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_view_mat();
}

void Camera::rotate_y(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_view_mat();
}

void Camera::calc_view_mat() {
  view = glm::inverse(translation * rotation);
}
