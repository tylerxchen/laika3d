#include "camera.hpp"

using namespace laika3d;

Camera::Camera(float fovy, float aspect, float near, float far)
  : projection(glm::perspective(fovy, aspect, near, far)), translation(1.0f), rotation(1.0f) {
  calc_view_mat();
}

void Camera::translate(float delta_x, float delta_y, float delta_z) {
  translation = glm::translate(translation, glm::vec3(delta_x, delta_y, delta_z));
  calc_view_mat();
}

void Camera::rotate_x(float delta_angle) {
  rotation = glm::rotate(rotation, delta_angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_view_mat();
}

void Camera::rotate_y(float delta_angle) {
  rotation = glm::rotate(rotation, delta_angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_view_mat();
}

void Camera::set_translation(float x, float y, float z) {
  translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_view_mat();
}

void Camera::set_rotation_x(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_view_mat();
}

void Camera::set_rotation_y(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_view_mat();
}

void Camera::calc_view_mat() {
  view = glm::inverse(translation * rotation);
}
